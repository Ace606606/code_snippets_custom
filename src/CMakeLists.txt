# src/CMakeLists.txt

set(LIB_TARGET "csc_core")
add_library(${LIB_TARGET} INTERFACE)
add_library(csc::core ALIAS ${LIB_TARGET})

add_subdirectory(utils)
add_subdirectory(daemon)

target_link_libraries(${LIB_TARGET} INTERFACE csc_utils)

target_include_directories(${LIB_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
