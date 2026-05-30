#pragma once
#include "csc/pipeline/network_types.hpp"

namespace csc::pipeline
{

struct [[gnu::packed]] EthernetHeader
{
     MacAddress dst_mac{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
     MacAddress src_mac{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
     uint16_t   type{ 0 };
};

struct [[gnu::packed]] ArpHeader
{
     uint16_t    hw_type{ byteswap16( 1 ) }; // Ethernet
     uint16_t    proto_type{ byteswap16( 0x0800 ) }; // IPv4
     uint8_t     hw_len{ 6 };
     uint8_t     proto_len{ 4 };
     uint16_t    opcode{ 0 };

     MacAddress  sender_mac{};
     Ipv4Address sender_ip{};
     MacAddress  target_mac{};
     Ipv4Address target_ip{};
};

} // namespace csc::pipeline