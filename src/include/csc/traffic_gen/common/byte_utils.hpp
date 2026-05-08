#pragma once
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <span>
#include <algorithm>

namespace csc::traffic_gen::common
{

inline void write16( uint8_t* buf, uint16_t v)
{
     uint16_t n = htons( v );
     std::memcpy( buf, &n, sizeof( n ) );
}

inline void write32( uint8_t* buf, uint32_t v )
{
     uint32_t n = htonl( v );
     std::memcpy( buf, &n, sizeof( n ) );
}

} // namespace csc::traffic_gen::common

inline void write16( uint8_t* buf, uint16_t v)
{
     std::span< uint8_t > buffer_view( buf,  2 );
     uint16_t n = htons( v );


     std::copy(  )
}