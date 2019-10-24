#pragma once

#include <vector>
#include <functional>
#include "heap.h"

class Sorter {
public:
  Sorter() = delete;

  template<
    typename Iter,
    typename Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
  static void insertion_sort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
    h_insertion_sort(begin, end, 1, cmp);
  }

  template<typename T, typename Cmp = std::less<T>>
  static void heap_sort(std::vector<T>& v, const Cmp& cmp = Cmp()) {
    Heap<T, Cmp>::heap_sort(v, cmp);
  }

  template<
    typename Iter,
    typename Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
  static void ciura_sort(Iter begin, Iter end, std::vector<long> gaps, const Cmp& cmp = Cmp()) {
  const std::vector<long> ciuras_gaps{701, 301, 132, 57, 23, 10, 4, 1};
    for (long gap : gaps) {
      h_insertion_sort(begin, end, gap, cmp);
    }
  }

  template<
    typename Iter,
    typename Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
  static void hibbard_sort(Iter begin, Iter end, std::vector<long> gaps, const Cmp& cmp = Cmp()) {
    long range = std::distance(begin, end);
    long gap = 2;
    while (gap << 1 < range) {
      gap = gap << 1;
    }
    for (long i = gap ; i > 1; i = i / 2 - 1) {
      h_insertion_sort(begin, end, i - 1, cmp);
    }
  }

private:
  template<
    typename Iter,
    typename Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
  static void h_insertion_sort(Iter begin, Iter end, unsigned h, const Cmp& cmp = Cmp()) {
    for (Iter i = begin; i != end; ++i) {
      Iter j = i - h;
      typename Iter::value_type x = *i;
      while (j != begin - 1 && cmp(*j, x)) {
        *(j + h) = *j;
        j -= h;
      }
      *(j + h) = x;
    }
  }

};

