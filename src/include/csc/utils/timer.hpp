#pragma once

#include "csc/utils/logger.hpp"

#include <chrono>
#include <string>
#include <string_view>

namespace csc::utils::timer
{

class Timer final
{
public:
     explicit Timer( std::string_view name ) : m_measurement_( name ), m_start_( std::chrono::steady_clock::now() ) {}
     ~Timer()
     {
          auto end = std::chrono::steady_clock::now();
          auto diff = end - m_start_;

          std::string unit;
          double value{};

          if( diff < std::chrono::microseconds( 1 ) )
          {
               value = static_cast< double >( std::chrono::duration_cast< std::chrono::nanoseconds >( diff ).count() );
               unit = "ns";
          }
          else if( diff < std::chrono::milliseconds( 1 ) )
          {
               value = static_cast< double >( std::chrono::duration_cast< std::chrono::microseconds >( diff ).count() );
               unit = "us";
          }
          else if( diff < std::chrono::seconds( 1 ) )
          {
               value = static_cast< double >( std::chrono::duration_cast< std::chrono::milliseconds >( diff ).count() );
               unit = "ms";
          }
          else
          {
               value = std::chrono::duration< double >( diff ).count();
               unit = "s";
          }

          csc::utils::logger::info( "[TIMER] {} : {} {}", m_measurement_, value, unit );
     }

private:
     std::string m_measurement_;
     std::chrono::time_point< std::chrono::steady_clock > m_start_;
};

} // namespace csc::utils::timer
