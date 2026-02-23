#include "utils/timer.hpp"

#include <ctime>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>

using namespace std::chrono_literals;
namespace timer = csc::utils::timer;

TEST(TimerTest, MeasureExecution)
{
     EXPECT_NO_THROW
     ({
          timer::Timer t( "TestMeasurement" );
          std::this_thread::sleep_for( 10ns );
     });
}

TEST(TimerTest, ScopeLogic)
{
     bool passed = false;
     
     {
          timer::Timer t( "ScopeTest" );
          std::this_thread::sleep_for( 10us );
          passed = true;
     }
     EXPECT_TRUE( passed );
}

TEST(TimerTest, IntegratedLoggerTest)
{
     {
          csc::utils::timer::Timer t( "IntegrationCheck" );
          std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
     }
     SUCCEED();
}