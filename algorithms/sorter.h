#pragma once

#include <vector>
#include "../data_structures/heap.h"

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
    Heap<T, Cmp> heap(v, compare);
    for (long i = v.size() - 1; i > 0; --i) {
      std::swap(v[0], v[i]);
      heap.decreaseSize();
      heap.downheap(0);
    }
  }

  private:
  template<typename Iter, typename Cmp>
  void h_insertion_sort(Iter begin, Iter end, unsigned h, Cmp comp) {
    for (Iter i = begin; i != end; i += h) {
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


