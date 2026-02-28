cmake_minimum_required(VERSION 3.28)
project(CodeSnippetsCustom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CSC_BUILD_EXTERNAL_DEPS "Build external dependencies" ON)
option(CSC_BUILD_EXAMPLES "Build examples application" ON)
option(CSC_BUILD_TESTS "Build tests" ON)
option(CSC_INSTALL "Install in system" OFF)
option(CSC_ENABLE_SANITIZERS "Enable sanitizers" OFF)
option(STRING_MODE "Treat warnings as errors" ON)

add_subdirectory(third_party)

if(CSC_BUILD_EXTERNAL_DEPS)
     list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
     include(Dependencies)
endif()

add_subdirectory(src)

if(CSC_BUILD_TESTS)
     enable_testing()
     add_subdirectory(test)
endif()

if(CSC_INSTALL)
     include(cmake/Packaging.cmake)
endif()

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