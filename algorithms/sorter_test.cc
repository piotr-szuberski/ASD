#include <assert.h>
#include <iostream>

#include "sorter.h"

void print_vector(std::vector<int>& v) {
  for (int i: v) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void heap_test() {
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

  std::vector<int> expected{0, 1, 3, 3, 4, 5};

  print_vector(asc_sorted);
  print_vector(desc_sorted);
  print_vector(shuffled);
  print_vector(empty);
  print_vector(singleton);
  assert(asc_sorted == expected);
  assert(desc_sorted == expected);
  assert(shuffled == expected);
  assert(empty == std::vector<int>());
  assert(singleton == std::vector<int>{2});


}

int main() {
  heap_test();
}
