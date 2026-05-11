# src/examples/CMakeLists.txt

add_executable(example_timer example_timer.cpp)
target_link_libraries(example_timer PRIVATE csc::utils)

add_executable(example_logger example_logger.cpp)
target_link_libraries(example_logger PRIVATE csc::utils)

add_executable(example_scope example_scope.cpp)
target_link_libraries(example_scope PRIVATE csc::utils)

add_executable(example_cli example_cli.cpp)
target_link_libraries(example_cli PRIVATE csc::utils)

add_executable(generator_value benchmarks/generator_value.cpp)
target_link_libraries(generator_value PRIVATE csc::utils)

add_executable(example_xor other/example_xor.cpp)
target_link_libraries(example_xor PRIVATE csc::utils)

set_target_properties(
     example_timer
     example_logger
     example_scope
     example_cli
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/examples"
)

set_target_properties(
     example_xor
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/examples/other"
)

set_target_properties(
     generator_value
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/examples/benchmarks"
)
