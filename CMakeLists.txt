cmake_minimum_required(VERSION 3.16.0)

project("ASD")
set(VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)

include(set_default_build_type.cmake)

SetDefaultBuildType("Debug")

set(CMAKE_VERBOSE_MAKEFILE OFF)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -Wno-error=dangling-else
    -Wshadow)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

message("Binary tree path: ${PROJECT_BINARY_DIR}")
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(test)
