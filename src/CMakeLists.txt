# src/CMakeLists.txt

set(LIB_TARGET "ext_sys_utils")
add_library(${LIB_TARGET} INTERFACE)
add_library(ext::sys::utils ALIAS ${LIB_TARGET})

target_include_directories(${LIB_TARGET} INTERFACE include)

if(TARGET fmt)
     target_link_libraries(${LIB_TARGET} INTERFACE fmt)
endif()

if(TARGET spdlog)
     target_link_libraries(${LIB_TARGET} INTERFACE spdlog::spdlog)
     target_compile_definitions(${LIB_TARGET} INTERFACE USE_SPDLOG)
endif()