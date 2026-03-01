#include "small_buffer_opt.hpp"

#include <array>
#include <functional>

#include "csc/utils/logger.hpp"
#include "csc/utils/timer.hpp"

namespace
{
std::size_t g_allocations{};
} // namespace

void* operator new( std::size_t size )
{
     g_allocations++;
     return std::malloc( size );
}

void operator delete( void* ptr ) noexcept
{
     std::free( ptr );
}

void* operator new[]( std::size_t size )
{
     g_allocations++;
     return std::malloc( size );
}

void operator delete[]( void* ptr ) noexcept
{
     std::free( ptr );
}

void operator delete( void* ptr, std::size_t ) noexcept
{
     std::free( ptr );
}

void operator delete[]( void* ptr, std::size_t ) noexcept
{
     std::free( ptr );
}

int main()
{
     static_assert( sizeof( Function ) == 64, "Size is not 64!" );
     static_assert( alignof( Function ) == 16, "Alignment is not 16!" );

     namespace logger = csc::utils::logger;
     using csc::utils::timer::Timer;

     logger::init_logger();
     const std::size_t iterations = 100'000;

     logger::info( "--- Starting SBO benchmark ({} iterations) ----", iterations );

     {
          g_allocations = 0;
          std::vector< Function > v;
          v.reserve( iterations );

          {
               Timer t( "Small objects creation (SBO)" );
               for( std::size_t i{}; i < iterations; ++i )
               {
                    size_t x{ i };
                    v.emplace_back(
                         [ x ]()
                         {
                              volatile size_t sink = x + 1;
                              ( void )sink;
                         } );
               }
          }

          logger::info( "Allocations for small objects: {}", g_allocations );

          {
               Timer t2( "Small object execution" );
               for( auto& f : v )
               {
                    f();
               }
          }
     }

     logger::info( "--------------------------------------------------------" );

     {
          g_allocations = 0;
          std::vector< Function > v;
          v.reserve( iterations );

          {
               Timer t( "Large objects creation (HEAP)" );
               for( std::size_t i{}; i < iterations; ++i )
               {
                    std::array< double, 10 > heavy_data{};
                    heavy_data[ 0 ] = static_cast< double >( i );

                    v.emplace_back(
                         [ heavy_data ]()
                         {
                              volatile double sink = heavy_data[ 0 ] + 1.0;
                              ( void )sink;
                         } );
               }
          }

          logger::info( "Allocations for large objects: {}", g_allocations );

          {
               Timer t2( "Large objects execution" );
               for( auto& f : v )
               {
                    f();
               }
          }
     }

     logger::info( "--------------------------------------------------------" );

     {
          g_allocations = 0;
          std::vector< std::function< void() > > v;
          v.reserve( iterations );

          {
               Timer t( "std::function ( standard sbo )" );
               for( std::size_t i{}; i < iterations; ++i )
               {
                    size_t x = i;
                    v.emplace_back(
                         [ x ]()
                         {
                              volatile size_t sink = x + 1;
                              ( void )sink;
                         } );
               }
          }

          logger::info( "Allocations for std::function: {}", g_allocations );

          {
               Timer t2( "std::function objects execution" );
               for( auto& f : v )
               {
                    f();
               }
          }
     }

     logger::info( "--------------------------------------------------------" );

     {
          g_allocations = 0;
          std::vector< std::function< void() > > v;
          v.reserve( iterations );

          {
               Timer t( "std::function ( standard heap )" );
               for( std::size_t i{}; i < iterations; ++i )
               {
                    std::array< size_t, 5 > x{};
                    x[ 0 ] = i;
                    v.emplace_back(
                         [ x ]()
                         {
                              volatile size_t sink = x[ 0 ] + 1;
                              ( void )sink;
                         } );
               }
          }

          logger::info( "Allocations for std::function: {}", g_allocations );

          {
               Timer t2( "std::function objects execution" );
               for( auto& f : v )
               {
                    f();
               }
          }
     }

     return 0;
}