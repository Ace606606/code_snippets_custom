# src/traffic_gen

add_executable(traffic_gen
     main.cpp
)
target_link_libraries(traffic_gen PRIVATE csc::utils)

set_target_properties(
     traffic_gen
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/traffic_gen"
)