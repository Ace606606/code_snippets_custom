#include <utils/logger.hpp>

namespace examples
{

namespace logger = csc::utils::logger;

void run_logger_demo()
{
     logger::init_logger();
     logger::info( "Starting logger example..." );

     std::string user = "Ace";
     logger::debug( "User '{}' is trying to log in", user );
     logger::error( "Connection failed for host: {}", "127.0.0.1" );
}

} // namespace examples

int main()
{
     examples::run_logger_demo();
     return 0;
}
