#include "csc/utils/logger.hpp"

int main()
{
     namespace log = csc::utils::logger;
     log::init_logger();
     log::info( "Run gen" );
     return 0;
}