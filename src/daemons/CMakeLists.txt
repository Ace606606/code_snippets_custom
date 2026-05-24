# src/daemon

add_library(csc_daemon)
add_library(csc::daemon ALIAS csc_daemon)

target_sources(csc_daemon
     PRIVATE
          load_daemon.cpp
)

target_link_libraries(csc_daemon
     PRIVATE
          csc::utils
)

target_compile_features(csc_daemon PUBLIC cxx_std_17)