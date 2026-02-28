#include "csc/daemon/load_daemon.hpp"
#include <csignal>
#include <fstream>
#include <optional>
#include "csc/utils/logger.hpp"

namespace csc::daemon::load_daemon
{

namespace logger = csc::utils::logger;

void LoadMonitor::run()
{
     setup_signals();
     logger::info( "Daemon started" );

     while( keep_running_ )
     {
          if( auto load = fetch_cpu_load() )
          {
               logger::info( "Current system load: {:.2f}", *load );
          }
          else
          {
               logger::error( "Failed to read CPU usage" );
          }

          std::unique_lock< std::mutex > lock( mtx_ );
          cv_.wait_for( lock, interval_, [] { return !keep_running_.load(); } );
     }
     logger::info( "Daemon exited gracefully" );
}

std::optional< double > LoadMonitor::fetch_cpu_load()
{
     static std::ifstream file( "/proc/loadavg" );
     if( !file.is_open() )
     {
          return std::nullopt;
     }
     file.clear();
     file.seekg( 0, std::ios::beg );
     double load{};
     return ( file >> load ) ? std::make_optional( load ) : std::nullopt;
}

void LoadMonitor::setup_signals()
{
     struct sigaction sa
     {};
     sa.sa_handler = []( int sig )
     {
          if( sig == SIGTERM || sig == SIGINT )
          {
               keep_running_ = false;
               cv_.notify_all();
          }
     };
     sigemptyset( &sa.sa_mask );
     sigaction( SIGTERM, &sa, nullptr );
     sigaction( SIGINT, &sa, nullptr );
}

} // namespace csc::daemon::load_daemon