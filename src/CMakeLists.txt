# src/CMakeLists.txt

add_subdirectory(utils)
add_subdirectory(daemons)
add_subdirectory(containers)

if(CSC_BUILD_EXAMPLES)
     add_subdirectory(examples)
endif()

if (CSC_BUILD_SANDBOX)
     add_subdirectory(sandbox)
endif()