#include <functional>

#include "gtest/gtest.h"

#include "../src/sorter.h"

// TODO get along with gtest
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

TEST(sorter, heap_sort) {
  std::vector<int> asc_sorted{0, 1, 3, 3, 4, 5};
  std::vector<int> desc_sorted{5, 4, 3, 3, 1, 0};
  std::vector<int> shuffled{5, 3, 3, 4, 1, 0};
  std::vector<int> empty{};
  std::vector<int> singleton{2};
  Sorter sorter;

  sorter.heap_sort(asc_sorted, std::greater<int>());
  sorter.heap_sort(desc_sorted, std::greater<int>());
  sorter.heap_sort(shuffled, std::greater<int>());
  sorter.heap_sort(empty, std::greater<int>());
  sorter.heap_sort(singleton, std::greater<int>());

  std::vector<int> expected{5, 4, 3, 3, 1, 0};

  EXPECT_EQ(asc_sorted, expected);
  EXPECT_EQ(desc_sorted, expected);
  EXPECT_EQ(shuffled, expected);
  EXPECT_EQ(empty, std::vector<int>());
  EXPECT_EQ(singleton, std::vector<int>{2});
}

TEST(sorter, insertion_sort) {
  std::vector<int> shuffled{5, 3, 3, 4, 1, 0};
  Sorter sorter;

  sorter.insertion_sort(shuffled.begin(), shuffled.end(), std::greater<int>());

  std::vector<int> expected{0, 1, 3, 3, 4, 5};

  EXPECT_EQ(shuffled, expected);
}
