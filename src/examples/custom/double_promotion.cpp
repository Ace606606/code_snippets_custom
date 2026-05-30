#include "csc/utils/logger.hpp"
#include "csc/utils/timer.hpp"
#include "csc/benchmark/do_not_optimize.hpp"

namespace csc::examples::custom
{

namespace log = csc::utils::logger;
using Timer = csc::utils::timer::Timer;

void test_double_promotion()
{
     log::info( "test_double_promotion" );

     volatile float f1 = 2.0F;
     volatile float f2 = 3.0F;
     volatile double d1 = 4.0;

     {
          Timer tm("float res = f1 * f2");
          for (int i = 0; i < 100'000'000; ++i) {
               [[maybe_unused]] float res = f1 * f2;
          }
     }

     {
          Timer tm( "double res = f1 * d1" );
          for ( int i = 0; i < 100'000'000; ++i )
          {
               [[maybe_unused]] double res = f1 * d1;
          }
     }

     // {
     //      Timer tm( "float res = f1 * d1" );
     //      for ( int i = 0; i < 100'000'000; ++i )
     //      {
     //           [[maybe_unused]] float res = f1 * d1; 
     //      }
     // }

     {
          Timer tm( "float res = d1 * d1" );
          for ( int i = 0; i < 100'000'000; ++i )
          {
               [[maybe_unused]] double res = d1 * d1; 
          }
     }

     // {
     //      Timer tm( "float res = d1 * d1" );
     //      for ( int i = 0; i < 100'000'000; ++i )
     //      {
     //           [[maybe_unused]] float res = d1 * d1; 
     //      }
     // }
}

void test_double_promotion2()
{
     log::info( "test_double_promotion2" );

     float f1 = 2.0F;
     float f2 = 3.0F;
     double d1 = 4.0;

     {
          Timer tm( "float res = f1 * f2" );
          for ( int i = 0; i < 100'000'000; ++i ) {
               float res = f1 * f2;
               csc::benchmark::DoNotOptimize( res );
          }
     }

     {
          Timer tm( "double res = f1 * d1" );
          for ( int i = 0; i < 100'000'000; ++i ) {
               double res = f1 * d1;
               csc::benchmark::DoNotOptimize( res );
          }
     }

     {
          Timer tm( "double res = d1 * d1" );
          for ( int i = 0; i < 100'000'000; ++i )
          {
               double res = d1 * d1;
               csc::benchmark::DoNotOptimize( res );
          }
     }
     

     // {
     //      Timer tm( "float res = d1 * d1" );
     //      for ( int i = 0; i < 100'000'000; ++i )
     //      {
     //           float res = d1 * d1;
     //           csc::benchmark::DoNotOptimize( res );
     //      }
     // }
}

} // namespace csc::examples::custom

namespace custom = csc::examples::custom;

int main()
{
     custom::test_double_promotion();
     custom::test_double_promotion2();
     return 0;
}