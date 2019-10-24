#include <functional>

#include "gtest/gtest.h"

#include "sort.h"

class SortTest: public ::testing::Test {
protected:
  void SetUp() override {
    empty = std::vector<int>{};
    singleton = std::vector<int>{3};
    asc = std::vector<int>{0, 1, 1, 1, 2, 3, 4, 5, 6, 7};
    desc = std::vector<int>{11, 11, 9, 5, 2, 2, -1, -3, -3, -5, -100};
    shuffledA = std::vector<int>{20, 5, -6, -2, -6, 99, 30, 321, 5, 4, 0 , 0, 2, 1, 31};
    shuffledB = shuffledA;
  }

  void verifyAll() {
    EXPECT_EQ(asc, ascSorted);
    EXPECT_EQ(desc, descSorted);
    EXPECT_EQ(shuffledA, shuffledSortedAsc);
    EXPECT_EQ(shuffledB, shuffledSortedDesc);
    EXPECT_EQ(empty, std::vector<int>{});
    EXPECT_EQ(singleton, std::vector<int>{3});
  }

  std::vector<int> empty;
  std::vector<int> singleton;
  std::vector<int> asc;
  std::vector<int> desc;
  std::vector<int> shuffledA;
  std::vector<int> shuffledB;

  const std::vector<int> ascSorted{0, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  const std::vector<int> descSorted{-100, -5, -3, -3, -1, 2, 2, 5, 9, 11, 11};
  const std::vector<int> shuffledSortedAsc{-6, -6, -2, 0, 0, 1, 2, 4, 5, 5, 20, 30, 31, 99, 321};
  const std::vector<int> shuffledSortedDesc{321, 99, 31, 30, 20, 5, 5, 4, 2, 1, 0, 0, -2, -6, -6};
};

TEST_F(SortTest, HeapSort) {
  Sort::HeapSort(asc);
  Sort::HeapSort(desc);
  Sort::HeapSort(shuffledA);
  Sort::HeapSort(shuffledB, std::less<int>());
  Sort::HeapSort(empty);
  Sort::HeapSort(singleton);
  verifyAll();
}

TEST_F(SortTest, InsertionSort) {
  Sort::InsertionSort(asc.begin(), asc.end());
  Sort::InsertionSort(desc.begin(), desc.end());
  Sort::InsertionSort(shuffledA.begin(), shuffledA.end());
  Sort::InsertionSort(shuffledB.begin(), shuffledB.end(), std::less<int>());
  Sort::InsertionSort(empty.begin(), empty.end());
  Sort::InsertionSort(singleton.begin(), singleton.end());
  verifyAll();
}

TEST_F(SortTest, CiuraSort) {
  Sort::CiuraSort(asc.begin(), asc.end());
  Sort::CiuraSort(desc.begin(), desc.end());
  Sort::CiuraSort(shuffledA.begin(), shuffledA.end());
  Sort::CiuraSort(shuffledB.begin(), shuffledB.end(), std::less<int>());
  Sort::CiuraSort(empty.begin(), empty.end());
  Sort::CiuraSort(singleton.begin(), singleton.end());
  verifyAll();
}

TEST_F(SortTest, ShellSort) {
  Sort::ShellSort(asc.begin(), asc.end());
  Sort::ShellSort(desc.begin(), desc.end());
  Sort::ShellSort(shuffledA.begin(), shuffledA.end());
  Sort::ShellSort(shuffledB.begin(), shuffledB.end(), std::less<int>());
  Sort::ShellSort(empty.begin(), empty.end());
  Sort::ShellSort(singleton.begin(), singleton.end());
  verifyAll();
}
