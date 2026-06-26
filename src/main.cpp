#include "csc/utils/logger.hpp"

namespace logger = csc::utils::logger;

int main()
{
     logger::init_logger( logger::LogLevel::debug );
     logger::info( "Hello world" );
     return 0;
}