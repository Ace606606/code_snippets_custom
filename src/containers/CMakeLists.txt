# src/containers/CMakeLists.txt

add_library(csc_containers STATIC)

add_library(csc::containers ALIAS csc_containers)

target_sources(csc_containers
     PRIVATE
          lru_cache.cpp
)

target_include_directories(csc_containers
     PUBLIC
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>
)

target_link_libraries(csc_containers
     PUBLIC
          csc::utils
)

target_compile_features(csc_containers PUBLIC cxx_std_17)