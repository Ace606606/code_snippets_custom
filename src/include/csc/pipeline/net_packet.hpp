#pragma once
#include <array>
#include <cstdint>

namespace csc::pipeline
{

template < std::size_t MaxSize = 1518 >
struct alignas( 64 ) NetPacket
{
     std::array< uint8_t, MaxSize > raw_buffer{};
     std::size_t length{ 0 };

     template < typename T >
     T* as( std::size_t offset = 0 )
     {
          return reinterpret_cast< T* >( raw_buffer.data() + offset );
     }

     template < typename T >
     const T* as( std::size_t offset = 0 ) const
     {
          return reinterpret_cast< const T* >( raw_buffer.data() + offset );
     }
};

} // namespace csc::pipeline