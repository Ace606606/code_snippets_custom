#include "daemon/load_daemon.hpp"
#include "utils/logger.hpp"

int main() {
    try {
        csc::utils::logger::init_logger();
        csc::daemon::load_daemon::LoadMonitor daemon;
        daemon.run();
    } catch (const std::exception& e) {
        csc::utils::logger::error("Critical failure: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}