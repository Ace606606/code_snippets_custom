# src/CMakeLists.txt

add_subdirectory(utils)


if(CSC_BUILD_TRAFFIC_GEN)
     add_subdirectory(traffic_gen)
endif()

if(CSC_BUILD_DAEMON)
     add_subdirectory(daemon)
endif()

if(CSC_BUILD_EXAMPLES)
     add_subdirectory(examples)
endif()

if(CSC_BUILD_PATTERNS)
     add_subdirectory(patterns)
endif()

if (CSC_BUILD_SANDBOX)
     add_subdirectory(sandbox)
endif()