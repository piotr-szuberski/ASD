cmake_minimum_required(VERSION 3.16.0)

project("ASD")

set(CMAKE_CXX_STANDARD 17)

#### https://cmake.org/cmake/help/latest/module/FetchContent.html ####
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
FetchContent_MakeAvailable(googletest)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# -DCMAKE_BUILD_TYPE=Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -v")
# -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

enable_testing()

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(HEADERS ${SRC_DIR}/sorter.h ${SRC_DIR}/heap.h)

set(TEST ${TEST_DIR}/sorter_test.cpp)

#add_library(asd STATIC ${src})
add_executable(sorter_test ${TEST} ${HEADERS} )
target_link_libraries(sorter_test PRIVATE gtest_main)

add_test(NAME sorter_test_test COMMAND sorter_test)
