# src/examples/CMakeLists.txt

add_executable(timer_example timer_example.cpp)
target_link_libraries(timer_example PRIVATE csc::utils)

add_executable(logger_example logger_example.cpp)
target_link_libraries(logger_example PRIVATE csc::utils)

add_executable(scope scope.cpp)
target_link_libraries(scope PRIVATE csc::utils)

set_target_properties(
     timer_example
     logger_example
     scope
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/examples"
)
