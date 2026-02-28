# src/daemon

add_library(csc_daemon)
add_library(csc::daemon ALIAS csc_daemon)

target_sources(csc_daemon
     PRIVATE
          load_daemon.cpp
)

target_include_directories(csc_daemon
     PUBLIC
          ${PROJECT_SOURCE_DIR}/src/include
)

target_link_libraries(csc_daemon
     PUBLIC
          csc::utils
)

target_compile_features(csc_daemon PUBLIC cxx_std_17)

# ---- executable wrapper ----

add_executable(csc-load-daemon main.cpp)

target_link_libraries(csc-load-daemon PRIVATE csc::daemon)
