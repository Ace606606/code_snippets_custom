# cmake/Dependencies.cmake

include(FetchContent)

option(CSC_BUILD_SPDLOG "Build spdlog" ON)
option(CSC_BUILD_GTEST "Build google tests" ON)
option(CSC_BUILD_CLI11 "Build cli11" ON)

if(CSC_BUILD_SPDLOG)
     message(STATUS "spdlog fetching from GitHub...")
     FetchContent_Declare(
          spdlog
          GIT_REPOSITORY https://github.com/gabime/spdlog.git
          GIT_TAG v1.17.0
     )
     set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE) # 
     FetchContent_MakeAvailable(spdlog)
endif()

if(CSC_BUILD_GTEST)
     message(STATUS "gtest fetching from GitHub...")
     FetchContent_Declare(
          googletest
          GIT_REPOSITORY https://github.com/google/googletest.git
          GIT_TAG v1.17.0
     )
     set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
     FetchContent_MakeAvailable(googletest)
endif()

if(CSC_BUILD_CLI11)
     message(STATUS "cli11 fething from GitHub...")
     FetchContent_Declare(
          cli11
          GIT_REPOSITORY https://github.com/CLIUtils/CLI11
          GIT_TAG v2.6.2
     )
     FetchContent_MakeAvailable(cli11)
endif()
