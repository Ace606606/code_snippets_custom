# src/patterns/ebo/CMakeLists.txt

add_executable(pattern_ebo ebo_example.cpp)

target_link_libraries(pattern_ebo
     PRIVATE
          csc::utils
)
