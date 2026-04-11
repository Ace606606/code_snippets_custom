# src/sandbox/CMakeLists.txt

add_executable(sandbox
     sandbox.cpp
)
target_link_libraries(sandbox PRIVATE csc::utils)

set_target_properties(
     sandbox
     PROPERTIES RUNTIME_OUTPUT_DIRECTORY
     "${CMAKE_BINARY_DIR}/sandbox"
)