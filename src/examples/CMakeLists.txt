# src/examples/CMakeLists.txt

function(add_example_bin SOURCE_FILE SUB_DIR)
     get_filename_component(BIN_NAME "${SOURCE_FILE}" NAME_WE)

     add_executable(${BIN_NAME} "${SOURCE_FILE}")
     
     target_link_libraries(${BIN_NAME} PRIVATE csc::utils)

     if(ARGN)
          target_link_libraries(${BIN_NAME} PRIVATE ${ARGN})
     endif()


     if(SUB_DIR STREQUAL "")
          set_target_properties(${BIN_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
     else()
          set_target_properties(${BIN_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${SUB_DIR}")
     endif()
endfunction()

add_example_bin(example_timer.cpp "")
add_example_bin(example_logger.cpp "")
add_example_bin(example_scope.cpp "")
add_example_bin(example_cli.cpp "")

add_example_bin(benchmarks/generator_value.cpp "benchmarks")

add_example_bin(other/example_xor.cpp "other")

add_example_bin(patterns/ebo_example.cpp "patterns")
add_example_bin(patterns/erase_remove_benchmark.cpp "patterns")
add_example_bin(patterns/sbo_benchmark.cpp "patterns")
add_example_bin(patterns/pimpl_example.cpp "patterns")

add_example_bin(daemons/example_load_daemon.cpp "daemons" csc::daemon)

add_example_bin(containers/example_lru_cache.cpp "containers")

file(GLOB CUSTOM_FILES "custom/*.cpp")

foreach(SOURCE_FILE ${CUSTOM_FILES})
     add_example_bin("${SOURCE_FILE}" "custom")
endforeach()

add_example_bin(pipeline/pipeline_arp.cpp "pipeline" csc::utils)