#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "utils/timer.hpp"

void test_heavy_computation( int count_elem )
{
     utils::Timer t( "Sort 10M elements" );

     std::vector< int > data( count_elem );
     for( int i{ 0 }; i < count_elem; ++i )
     {
          std::sqrt( i );
     }

     std::sort( data.begin(), data.end() );
}

int main()
{
     std::cout << "--- Starting performance test ---" << std::endl;

     constexpr int count_elem = 1000000;

     test_heavy_computation( count_elem );

     {
          utils::Timer t( "Scoped block test" );
          for( int i{}; i < count_elem; ++i )
          {
               std::sqrt( i );
          }
     }

     std::cout << "--- Starting performance test ---" << std::endl;
}