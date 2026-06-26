cmake_minimum_required(VERSION 3.28)
project(CodeSnippetsCustom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CSC_BUILD_EXTERNAL_DEPS "Build external dependencies" ON)
option(CSC_ENABLE_SANITIZERS "Enable sanitizers" OFF)
option(STRICT_MODE "Treat warnings as errors" ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
set(SPDLOG_BUILD_STATIC ON CACHE BOOL "Build spdlog as static lib" FORCE)

# ---- warnings ----
add_library(csc_warnings INTERFACE)

target_compile_options(csc_warnings INTERFACE
     $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
          -Wall               # base warn
          -Wextra             # additional warn
          -Wpedantic          # string standard verification
          -Wconversion        # (double -> int)
          -Wsign-conversion   # (int -> uint)
          -Wnon-virtual-dtor   
          -Wshadow

          $<$<BOOL:${STRICT_MODE}>:-Werror>
     >
)

# ---- sanitizers ----
add_library(csc_sanitizers INTERFACE)

if (CSC_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
     target_compile_options(csc_sanitizers INTERFACE
          -fsanitize=address       # SEGF
          -fsanitize=undefined     # UB
     )
     target_link_options(csc_sanitizers INTERFACE
          -fsanitize=address
          -fsanitize=undefined
     )
endif()


add_subdirectory(third_party)
add_subdirectory(src)