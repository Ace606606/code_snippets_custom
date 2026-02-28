# src/patterns/erase_remove/CMakeLists.txt

add_executable(pattern_erase_benchmark erase_remove_benchmark.cpp)

target_link_libraries(pattern_erase_benchmark
     PRIVATE
          csc::utils
)
