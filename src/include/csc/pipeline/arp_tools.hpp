#pragma once

#include <optional>

#include <csc/utils/logger.hpp>
#include "csc/pipeline/net_packet.hpp"
#include "csc/pipeline/protocols.hpp"
#include "csc/pipeline/network_types.hpp"

namespace csc::pipeline
{

namespace log = csc::utils::logger;

class ArpTools
{

public:
     struct ParsedArpInfo
     {
          uint16_t    opcode;
          MacAddress  sender_mac;
          Ipv4Address sender_ip;
          MacAddress  target_mac;
          Ipv4Address target_ip;
     };

     template < std::size_t MaxSize >
     static NetPacket< MaxSize > createPacket(
          uint16_t opcode,
          const MacAddress& src_mac, const Ipv4Address& src_ip,
          const MacAddress& dst_mac, const Ipv4Address& dst_ip
     )
     {
          NetPacket< MaxSize > packet;
          packet.length = sizeof( EthernetHeader ) + sizeof( ArpHeader );

          static_assert( MaxSize >= ( sizeof( EthernetHeader ) + sizeof( ArpHeader ) ),
                         "MaxSize too small for Arp Packet" );

          auto* eth = packet.template as< EthernetHeader >( 0 );
          eth->src_mac = src_mac;
          eth->dst_mac = ( opcode == arp_op::request ) ? MacAddress{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } : dst_mac;
          eth->type = ether_type::arp;

          auto* arp = packet. template as< ArpHeader >( sizeof( EthernetHeader ) );
          arp->opcode = opcode;
          arp->sender_mac = src_mac;
          arp->sender_ip = src_ip;
          arp->target_mac = ( opcode == arp_op::request ) ? MacAddress{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } : dst_mac;
          arp->target_ip = dst_ip;

          return packet;
     }

     template< std::size_t MaxSize >
     static std::optional< ParsedArpInfo > parseAndValidate( const NetPacket< MaxSize >& packet )
     {
          constexpr size_t min_required_len = sizeof( EthernetHeader ) + sizeof( ArpHeader );
          
          if( packet.length < min_required_len )
          {
               return std::nullopt;
          }

          const auto* eth = packet.template as< EthernetHeader >( 0 );

          if( eth->type != ether_type::arp )
          {
               return std::nullopt;
          }

          const auto* arp = packet.template as< ArpHeader >( sizeof( EthernetHeader ) );

          ParsedArpInfo info{};
          info.opcode     = byteswap16( arp->opcode );
          info.sender_mac = arp->sender_mac;
          info.sender_ip  = arp->sender_ip;
          info.target_mac = arp->target_mac;
          info.target_ip  = arp->target_ip;

          return info;
     }

     static void logArp( const std::optional< ParsedArpInfo >& info )
     {
          if( info.has_value() )
          {
               log::info( 
                    "ArpTools: received ParsedArpInfo opcode={}\nsender mac={} sender_ip={}\ntarget_mac={} target_ip={} ",
                    info->opcode,
                    info->sender_mac,
                    info->sender_ip,
                    info->target_mac,
                    info->target_ip
               );
               return;
          }

          log::warn( "ArpTools: received nullopt" );
     }
};

}; // namespace csc::pipeline

