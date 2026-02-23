#include "utils/logger.hpp"

#include <gtest/gtest.h>

int main( int argc, char** argv )
{
     csc::utils::logger::init_logger();
     ::testing::InitGoogleTest( &argc, argv );
     return RUN_ALL_TESTS();
}