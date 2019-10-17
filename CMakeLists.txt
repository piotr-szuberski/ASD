cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 14)

project(ASD)

# -DCMAKE_BUILD_TYPE=Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
# -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(TEST ${TEST_DIR}/sorter_test.cpp)
set(HEADERS ${SRC_DIR}/sorter.h ${SRC_DIR}/heap.h)

add_executable(sorter_test ${TEST} ${HEADERS} )
