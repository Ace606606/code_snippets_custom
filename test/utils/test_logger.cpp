#include "csc/utils/logger.hpp"

#include <gtest/gtest.h>

namespace logger = csc::utils::logger;

TEST( LoggerTest, InitTest )
{
     EXPECT_NO_THROW
     ({
          logger::init_logger();
     });
}

TEST( LoggerTest, Formatting )
{
     EXPECT_NO_THROW
     ({
          logger::info( "Hello, {}!", "World" );
          logger::debug( "Value {}", 42 );
          logger::error( "Error code: 0x{:X}", 255 );
     });
}