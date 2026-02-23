#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>

namespace csc::daemon::load_daemon
{

class LoadMonitor
{
public:
     LoadMonitor() = default;
     ~LoadMonitor() = default;

     LoadMonitor( const LoadMonitor& ) = delete;
     LoadMonitor& operator=( const LoadMonitor& ) = delete;

     void run();

private:
     std::optional< double > fetch_cpu_load();
     void setup_signals();

     static constexpr std::chrono::seconds interval_{ 10 };
     static inline std::atomic< bool > keep_running_{ true };
     static inline std::condition_variable cv_;
     static inline std::mutex mtx_;
};

} // namespace csc::daemon::load_daemon