#include "csc/utils/timer.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace examples
{

using Timer = csc::utils::timer::Timer;

void test_heavy_computation( int count_elem )
{
     Timer t( "Sort 10M elements" );

     std::vector< int > data( count_elem );
     for( int i{ 0 }; i < count_elem; ++i )
     {
          std::sqrt( i );
     }

     std::sort( data.begin(), data.end() );
}

} // namespace examples

int main()
{
     std::cout << "--- Starting performance test ---" << std::endl;

     constexpr int count_elem = 1000000;

     examples::test_heavy_computation( count_elem );

     std::cout << "--- Starting performance test ---" << std::endl;
}
