cmake_minimum_required(VERSION 3.5)
project(long_arithmetic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS  "/EHsc /O2 /Ob2 /Ot /Oi /fp:fast")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${SOURCE_DIR})

add_executable(demonstration ${TEST_DIR}/demonstration.cpp 
${SOURCE_DIR}/long_arithmetic.cpp ${SOURCE_DIR}/modular_arithmetic.cpp ${SOURCE_DIR}/operators.cpp ${SOURCE_DIR}/digit.cpp)

add_executable(benchmark ${TEST_DIR}/benchmark.cpp 
${SOURCE_DIR}/long_arithmetic.cpp ${SOURCE_DIR}/modular_arithmetic.cpp ${SOURCE_DIR}/operators.cpp ${SOURCE_DIR}/digit.cpp)

ADD_SUBDIRECTORY(googletest-release-1.10.0)
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ${TEST_DIR}/unit_test.cpp 
${SOURCE_DIR}/long_arithmetic.cpp ${SOURCE_DIR}/modular_arithmetic.cpp ${SOURCE_DIR}/operators.cpp ${SOURCE_DIR}/digit.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
add_test(runUnitTests runUnitTests)