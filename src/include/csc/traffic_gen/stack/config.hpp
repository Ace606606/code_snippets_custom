#pragma once
#include <array>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace csc::traffic_gen::stack
{

struct EthernetConfig
{
     std::array< uint8_t, 6 > src_mac{};
     std::array< uint8_t, 6 > dst_mac{};
     uint16_t ethertype{ 0x0800 }; // IPv4
};

struct ArpConfig
{
     uint16_t hardware_type{ 1 };
     uint16_t protocol_type{ 0x0800 };
     uint8_t hardware_len{ 6 };
     uint8_t protocol_len{ 4 };
     uint16_t operation{ 1 };

     std::array< uint8_t, 6 > sender_mac{};
     uint32_t sender_ip{};
     std::array< uint8_t, 6 > target_mac{};
     uint32_t target_ip{};
};

struct IcmpCongig
{
     uint8_t type{ 8 };
     uint8_t code{};
     uint16_t checksum{};
     uint16_t identifier{};
     uint16_t sequence{};
};

struct IPv4Config
{
     uint32_t src_ip{};
     uint32_t dst_ip{};
     uint8_t ttl{ 64 };
     uint8_t tos{};
     uint16_t id{};
     bool df{ false };
};

enum class IPProtocol : uint8_t
{
     TCP = 6,
     UDP = 17
};

struct TCPConfig
{
     uint16_t src_port{};
     uint16_t dst_port{};

     uint16_t window{ 65535 };
     uint8_t data_offset{ 5 };

     struct Flags
     {
          bool syn{ false };
          bool ack{ false };
          bool fin{ false };
          bool rst{ false };
          bool psh{ false };
          bool urg{ false };

     } flags;
};

struct UDPConfig
{
     uint16_t src_port{};
     uint16_t dst_port{};
};

struct PayloadConfig
{
     std::vector< uint8_t > data;
};

struct FlowConfig
{
     bool stateful = true;
     uint32_t initial_seq{ 1000 };
     uint32_t initial_ack{ 0 };
};

struct IPv4Stack
{
     IPv4Config header;
     std::variant< TCPConfig, UDPConfig > l4;
     PayloadConfig payload;
     FlowConfig flow;

     IPProtocol get_l4_proto() const
     {
          return std::visit(
               []( auto&& arg )
               {
                    using T = std::decay_t< decltype( arg ) >;
                    if constexpr( std::is_same_v< T, TCPConfig > )
                    {
                         return IPProtocol::TCP;
                    }
                    return IPProtocol::UDP;
               },
               l4 );
     }

     std::pair< uint16_t, uint16_t > get_ports() const
     {
          return std::visit( []( auto&& arg ) { return std::make_pair( arg.src_port, arg.dst_port ); }, l4 );
     }
};

using L3Variant = std::variant< ArpConfig, IPv4Stack >;

struct PacketConfig
{
     EthernetConfig l2;
     L3Variant l3;

     uint16_t get_ethertype() const
     {
          return std::visit(
               []( auto&& arg ) -> uint16_t
               {
                    using T = std::decay_t< decltype( arg ) >;
                    if constexpr( std::is_same_v< T, IPv4Stack > )
                    {
                         return 0x0800;
                    }
                    if constexpr( std::is_same_v< T, ArpConfig > )
                    {
                         return 0x0806;
                    }
               },
               l3 );
     }
};

} // namespace csc::traffic_gen::stack