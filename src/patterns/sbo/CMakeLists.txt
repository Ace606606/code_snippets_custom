add_executable(sbo_benchmark sbo_benchmark.cpp)
target_include_directories(sbo_benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sbo_benchmark PRIVATE csc::utils)