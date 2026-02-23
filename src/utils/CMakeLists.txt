# src/utils/CMakeLists.txt

set(LIB_TARGET "csc_utils")
add_library(${LIB_TARGET} INTERFACE)
add_library(csc::utils ALIAS ${LIB_TARGET})

target_include_directories(${LIB_TARGET} INTERFACE ${CMAKE_SOURCE_DIR}/src)

if(TARGET fmt)
     target_link_libraries(${LIB_TARGET} INTERFACE fmt::fmt)
endif()

if(TARGET spdlog)
     target_link_libraries(${LIB_TARGET} INTERFACE spdlog::spdlog)
endif()

target_link_libraries(${LIB_TARGET} INTERFACE spdlog::spdlog fmt::fmt)

if(TARGET spdlog)
     target_compile_definitions(${LIB_TARGET} INTERFACE USE_SPDLOG)
endif()