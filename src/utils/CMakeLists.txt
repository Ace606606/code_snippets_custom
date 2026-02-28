# src/utils/CMakeLists.txt

add_library(csc_utils INTERFACE)
add_library(csc::utils ALIAS csc_utils)

target_include_directories(csc_utils INTERFACE ${PROJECT_SOURCE_DIR}/src/include)

target_link_libraries(csc_utils
     INTERFACE
          csc_warnings
          csc_sanitizers
)

if(TARGET fmt)
     target_link_libraries(csc_utils INTERFACE fmt::fmt)
endif()

if(TARGET spdlog)
     target_link_libraries(csc_utils INTERFACE spdlog::spdlog)
     target_compile_definitions(csc_utils INTERFACE USE_SPDLOG)
endif()
