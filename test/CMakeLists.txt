
#### https://cmake.org/cmake/help/latest/module/FetchContent.html ####
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(sort_test sort_test.cpp)
target_link_libraries(sort_test PRIVATE gtest_main)

add_test(NAME sorter COMMAND sort_test)
