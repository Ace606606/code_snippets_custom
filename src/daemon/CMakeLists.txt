# src/daemon

add_executable(csc-load-daemon
     main.cpp
     load_daemon.cpp
     load_daemon.hpp
)

target_link_libraries(csc-load-daemon PRIVATE csc_utils)
