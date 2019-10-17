#pragma once

#include <vector>
#include "heap.h"

class Sorter {
  public:

  template<typename T>
  static bool less(const T& t1, const T& t2) {
    return t1 < t2;
  }

  template<typename T>
  static bool greater(const T& t1, const T& t2) {
    return t1 > t2;
  }

  template<typename Iter, typename Cmp>
  void insertion_sort(Iter begin, Iter end, Cmp comp) {
    h_insertion_sort(begin, end, 1, comp);
  }

  template<typename T, typename Cmp>
  void heap_sort(std::vector<T>& v, Cmp compare) {
    Heap<T, Cmp>::heap_sort(v, compare);
  }

  template<typename Iter, typename Cmp>
  void shell_sort(Iter begin, Iter end, Cmp comp, std::vector<long> gaps) {
    for (long gap : gaps) {
      h_insertion_sort(begin, end, gap, comp);
    }
  }

  const std::vector<long> ciuras_gaps{701, 301, 132, 57, 23, 10, 4, 1};

  std::vector<long> hibbard_gaps(long n) {
    std::vector<long> gaps{1};
    long gap = 2;
    do {
      gaps.push_back(gap * 2 - 1);
      gap *= 2;
    } while (gap < n);
    return gaps;
  }

  private:
  template<typename Iter, typename Cmp>
  void h_insertion_sort(Iter begin, Iter end, unsigned h, Cmp comp) {
    for (Iter i = begin; i != end; ++i) {
      Iter j = i - h;
      typename Iter::value_type x = *i;
      while (j != begin - 1 && comp(*j, x)) {
        *(j + h) = *j;
        j -= h;
      }
      *(j + h) = x;
    }
  }

};

