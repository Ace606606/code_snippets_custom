include(FetchContent)

option(BUILD_SPDLOG "Build external dependencies" ON)

if(BUILD_SPDLOG)
     message(STATUS "Checking for spdlog...")

     if(spdlog_FOUND)
          message(STATUS "Found spdlog in system")
     else()
          message(STATUS "spdlog not found, fetching from GitHub...")
          FetchContent_Declare(
               spdlog
               GIT_REPOSITORY https://github.com/gabime/spdlog.git
               GIT_TAG v1.17.0
          )
          set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
          FetchContent_MakeAvailable(spdlog)
     endif()
endif()