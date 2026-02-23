#include "utils/timer.hpp"

#include <ctime>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>

using namespace std::chrono_literals;
namespace timer = ext::sys::utils::timer;

TEST(TimerTest, MeasureExecution)
{
     EXPECT_NO_THROW
     ({
          timer::Timer t( "TestMeasurement" );
          std::this_thread::sleep_for( 10ms );
     });
}

TEST(TimerTest, ScopeLogic)
{
     bool passed = false;
     
     {
          timer::Timer t( "ScopeTest" );
          std::this_thread::sleep_for( 5ms );
          passed = true;
     }
     EXPECT_TRUE( passed );
}