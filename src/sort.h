#pragma once

#include <vector>
#include <functional>
#include "heap.h"

/** By deafault sorts ascending */
class Sort {
public:
  Sort() = delete;

  template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void InsertionSort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
    HInsertionSort(begin, end, 1, cmp);
  }

  template<typename T, typename Cmp = std::greater<T>>
  static void HeapSort(std::vector<T>& v, const Cmp& cmp = Cmp()) {
    Heap<T, Cmp>::HeapSort(v, cmp);
  }

  template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void CiuraSort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
  const std::vector<long> ciuras_gaps{701, 301, 132, 57, 23, 10, 4, 1};
    for (long gap : ciuras_gaps) {
      HInsertionSort(begin, end, gap, cmp);
    }
  }

  template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void ShellSort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
    long range = std::distance(begin, end);
    long gap = 2;
    while (gap << 1 < range) {
      gap = gap << 1;
    }
    for (long i = gap ; i > 1; i = i / 2) {
      HInsertionSort(begin, end, i - 1, cmp);
    }
  }

private:
  template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void HInsertionSort(Iter begin, Iter end, long h, const Cmp& cmp = Cmp()) {
    for (Iter i = begin + h; std::distance(i, end) > 0; ++i) {
      Iter j = i - h;
      typename Iter::value_type x = *i;
      while (std::distance(begin, j) >= 0 && cmp(*j, x)) {
        *(j + h) = *j;
        j -= h;
      }
      *(j + h) = x;
    }
  }

};

