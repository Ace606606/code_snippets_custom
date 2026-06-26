add_subdirectory(utils)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
    csc_utils
    csc_warnings
    csc_sanitizers
)