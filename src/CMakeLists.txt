# src/CMakeLists.txt

add_subdirectory(utils)
add_subdirectory(daemon)

if(CSC_BUILD_EXAMPLES)
     add_subdirectory(examples)
endif()

if(CSC_BUILD_PATTERNS)
     add_subdirectory(patterns)
endif()