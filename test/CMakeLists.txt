# test/CMakeLists.txt

if(NOT TARGET gtest AND NOT TARGET GTest::gtest)
     message(FATAL_ERROR "Google test not found! Check CSC_BUILD_GTEST option")
endif()

set(UNIT_TEST "unit_test")

file(GLOB_RECURSE TEST_UTILS CONFIGURE_DEPENDS
     "utils/*.cpp"
)

add_executable(${UNIT_TEST} 
     "test_main.cpp"
     ${TEST_UTILS}
)

target_link_libraries(${UNIT_TEST}
     PRIVATE
     csc::utils
     GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(${UNIT_TEST})