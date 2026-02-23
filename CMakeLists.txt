cmake_minimum_required(VERSION 3.28)
project(CodeSnippetsCustom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CSC_BUILD_EXTERNAL_DEPS "Build external dependencies" ON)
option(CSC_BUILD_EXAMPLES "Build example application" ON)
option(CSC_BUILD_TESTS "Build tests" ON)

add_subdirectory(third_party)

if(CSC_BUILD_EXTERNAL_DEPS)
     list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
     include(Dependencies)
endif()

add_subdirectory(src)

if(CSC_BUILD_EXAMPLES)
     add_subdirectory(src/examples)
endif()

if(CSC_BUILD_TESTS)
     enable_testing()
     add_subdirectory(test)
endif()
