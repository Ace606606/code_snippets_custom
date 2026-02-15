#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace utils
{

class Timer final
{
public:
     explicit Timer( const std::string& name ) : m_measurement_( name ), m_start_( std::chrono::steady_clock::now() ) {}
     ~Timer()
     {
          auto end = std::chrono::steady_clock::now();
          std::chrono::duration diff = end - m_start_;

          std::cout << "[TIMER] " << m_measurement_ << " : ";

          if( diff < std::chrono::milliseconds( 1 ) )
          {
               auto us = std::chrono::duration_cast< std::chrono::microseconds >( diff ).count();
               std::cout << us << " us";
          }
          else if( diff < std::chrono::seconds( 1 ) )
          {
               auto ms = std::chrono::duration_cast< std::chrono::milliseconds >( diff ).count();
               std::cout << ms << " ms";
          }
          else
          {
               auto s = std::chrono::duration< double >( diff ).count();
               std::cout << s << " s";
          }
          std::cout << std::endl;
     }

private:
     std::string m_measurement_;
     std::chrono::time_point< std::chrono::steady_clock > m_start_;
};

} // namespace utils