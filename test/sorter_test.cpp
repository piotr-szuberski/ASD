#include <assert.h>
#include <iostream>
#include <functional>
#include "gtest/gtest.h"

#include "../src/sorter.h"


// simple sequence printer
// http://coliru.stacked-crooked.com/a/f031bcac76d6e430
template< typename T, template<class,class...> class V, class... Args>
std::ostream& operator <<(std::ostream& os, const V<T,Args...>& seq)
{
    for (auto const& x : seq)
        os << x << ' ';
    return os;
}

// TODO get along with gtest
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

// void print_vector(std::vector<int>& v) {
//   for (int i: v) {
//     std::cout << i << ' ';
//   }
//   std::cout << '\n';
// }

// // void heap_test() {
TEST(sorter, heap_sort) {
  std::vector<int> asc_sorted{0, 1, 3, 3, 4, 5};
  std::vector<int> desc_sorted{5, 4, 3, 3, 1, 0};
  std::vector<int> shuffled{5, 3, 3, 4, 1, 0};
  std::vector<int> empty{};
  std::vector<int> singleton{2};
  Sorter sorter;

  sorter.heap_sort(asc_sorted, Sorter::greater<int>);
  sorter.heap_sort(desc_sorted, Sorter::greater<int>);
  sorter.heap_sort(shuffled, Sorter::greater<int>);
  sorter.heap_sort(empty, Sorter::greater<int>);
  sorter.heap_sort(singleton, Sorter::greater<int>);

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

// // void shell_sort_test() {
// TEST (sorter, shell_sort) {
//   Sorter sorter;
//   for (int i = 0; i < 2; ++i) {
//     std::vector<long> gaps = (i == 0) ? sorter.ciuras_gaps : sorter.hibbard_gaps(6);
//     std::vector<int> asc_sorted{0, 1, 3, 3, 4, 5};
//     std::vector<int> desc_sorted{5, 4, 3, 3, 1, 0};
//     std::vector<int> shuffled{5, 3, 3, 4, 1, 0};
//     std::vector<int> empty{};
//     std::vector<int> singleton{2};

//     std::vector<int> expected{5, 4, 3, 3, 1, 0};

//     sorter.shell_sort(asc_sorted.begin(), asc_sorted.end(), Sorter::greater<int>, gaps);
//     sorter.shell_sort(desc_sorted.begin(), desc_sorted.end(), Sorter::greater<int>, gaps);
//     sorter.shell_sort(shuffled.begin(), shuffled.end(), Sorter::greater<int>, gaps);
//     sorter.shell_sort(empty.begin(), empty.end(), Sorter::greater<int>, gaps);
//     sorter.shell_sort(singleton.begin(), singleton.end(), Sorter::greater<int>, gaps);

//     EXPECT_EQ(asc_sorted, expected);
//     EXPECT_EQ(desc_sorted, expected);
//     EXPECT_EQ(shuffled, expected);
//     EXPECT_EQ(empty, std::vector<int>());
//     EXPECT_EQ(singleton, std::vector<int>{2});
//   }
// }

// // int main() {
// //   heap_test();
// // }
