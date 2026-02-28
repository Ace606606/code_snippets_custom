add_executable(pattern_pimpl main.cpp pimpl_example.cpp)

target_include_directories(pattern_pimpl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pattern_pimpl
     PRIVATE
          csc::utils
)
