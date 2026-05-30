#pragma once
#include <array>
#include <cstdint>
#include "fmt/base.h"

namespace csc::pipeline
{

using MacAddress = std::array< uint8_t, 6 >;
using Ipv4Address = std::array< uint8_t, 4 >;

constexpr uint16_t byteswap16( uint16_t value )
{
     return static_cast< uint16_t >( ( value << 8 ) | ( value >> 8 ) );
}

constexpr uint32_t byteswap32( uint32_t value )
{
     return (( value << 24 ) & 0xff000000 ) |
            (( value << 8 )  & 0x00ff0000 ) |
            (( value >> 8 )  & 0x0000ff00 ) |
            (( value >> 24 ) & 0x000000ff );
}

namespace ether_type
{

constexpr uint16_t arp = byteswap16( 0x0806 );
constexpr uint16_t ipv4 = byteswap16( 0x0800 );

}

namespace arp_op
{

constexpr uint16_t request = byteswap16( 1 );
constexpr uint16_t replay = byteswap16( 2 );

}

} // namespace csc::pipeline

template<>
struct fmt::formatter< csc::pipeline::MacAddress >
{
     constexpr auto parse( format_parse_context& ctx )
     {
          return ctx.begin();
     }

     auto format( const csc::pipeline::MacAddress& mac, format_context& ctx ) const
     {
          return fmt::format_to(
               ctx.out(), "{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}",
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]
          );
     }
};

template <>
struct fmt::formatter< csc::pipeline::Ipv4Address >
{
     constexpr auto parse( format_parse_context& ctx )
     {
          return ctx.begin();
     }

     auto format( const csc::pipeline::Ipv4Address& ip, format_context& ctx ) const
     {
          return fmt::format_to(
               ctx.out(), "{}.{}.{}.{}",
               ip[0], ip[1], ip[2], ip[3]
          );
     }
};