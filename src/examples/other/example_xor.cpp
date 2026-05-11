#include <cstdint>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <cassert>
#include "csc/utils/logger.hpp"

namespace examples
{
namespace log = csc::utils::logger;

void view_logic()
{
     log::info( "{:=^{}}", " Run XOR ", 50 );

     uint8_t value = 1;
     auto overflow = static_cast< uint8_t >( value << 8 );

     log::info( "{0}:{0:#010b}. << 1: {1}:{1:#010b}. << 2: {2}:{2:#010b}. << 4: {3}:{3:#010b}. << 8: {4}:{4:#010b}.", value,
          value << 1, value << 2, value << 4, overflow );

     value = 255;
     auto zero = static_cast< uint8_t >( value >> 8 );

     log::info( "{0}:{0:#010b}. >> 1: {1}:{1:#010b}. >> 2: {2}:{2:#010b}. >> 4: {3}:{3:#010b}. >> 8: {4}:{4:#010b}.", value,
          value >> 1, value >> 2, value >> 4, zero );
}

template< typename T >
bool check_signed( T value )
{
     if constexpr( std::is_arithmetic_v< T > && std::is_signed_v< T > )
     {
          /// litle engine
          // auto* raw_ptr = reinterpret_cast< uint8_t* >( &value );
          // uint8_t last_byte = raw_ptr[ sizeof( T ) - 1 ]; // NOLINT
          // return ( last_byte >> 7 ) & 1;
          return value < 0;
     }
     return false;
}

void check_tuple()
{
     using SignedTrue = std::tuple< int8_t, int16_t, int32_t, int64_t, float, double >;
     using SignedFalse = std::tuple< uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double, std::string >;
     
     SignedTrue tuple_true = std::make_tuple( -1, -1, -1, -1, -1.0F, -1.0 );
     SignedFalse tuple_false{ 1, '1', 1, 1, 1, 1, 1, 1, 1, 1, "-1" };

     std::apply( []( auto&&... args ){
          ( ( !check_signed( args ) ? log::error( "Error" ) : void() ), ... ); // Fold expression
     }, tuple_true );

     std::apply( []( auto&&... args ){
          ( ( check_signed( args ) ? log::error( "Error" ) : void() ), ... );
     }, tuple_false );
}

/// integreal promaotion
void check_types()
{
     uint8_t x = 1;
     uint8_t y = 1;

     using ResultType = decltype( x + y );

     log::info( "Type of (x + y) is: {}", typeid( ResultType ).name() );
     log::info( "Size of (x + y) is {} bytes", sizeof( x + y ) );

     if constexpr( std::is_same_v< ResultType, int > )
     {
          log::info( "Confirmed: it`s a standard singed int" );
     }
}
} // namespace examples

int main()
{
     // examples::view_logic();
     //  examples::check_types();
     examples::check_tuple();

     return 0;
}