cmake_minimum_required(VERSION 2.8)

project(ASD)


set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(TEST ${TEST_DIR}/sorter_test.cpp)
set(HEADERS ${SRC_DIR}/sorter.h ${SRC_DIR}/heap.h)

add_executable(sorter_test ${TEST} ${HEADERS} )
