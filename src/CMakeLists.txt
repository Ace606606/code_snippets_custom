# src/CMakeLists.txt

add_subdirectory(utils)
add_subdirectory(daemon)

if(CSC_BUILD_EXAMPLES)
     add_subdirectory(examples)
endif()

