cmake_minimum_required(VERSION 3.16)

add_subdirectory(../lib lib)

include_directories(${SHARED_LIB_INCLUDE_DIR})

set(SRCS Calcs_test.cpp)
add_executable(Calcs_test ${SRCS})
target_link_libraries(
    Calcs_test
    lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Calcs_test)