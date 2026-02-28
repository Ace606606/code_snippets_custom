#include "csc/utils/logger.hpp"

int main()
{
     namespace logger = csc::utils::logger;
     logger::init_logger();

     logger::info("Run test internal scope");
     //csc::daemon::load_daemon::LoadMonitor t;
}