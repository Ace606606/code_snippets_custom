cmake_minimum_required(VERSION 3.28)
project(CodeSnippetsCustom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_EXTERNAL_DEPS "Build external dependencies" ON)
option(BUILD_EXAMPLES "Build example application" ON)

add_subdirectory(third_party)

if(BUILD_EXTERNAL_DEPS)
     list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
     include(Dependencies)
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
     add_subdirectory(src/examples)
endif()
