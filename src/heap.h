#pragma once
#include <vector>

/*
  greater - min heap
  less - max heap
 */
template<typename T, typename Cmp = std::less<T>>
class Heap {
public:
  Heap(std::vector<T>& in, const Cmp& cmp = Cmp()) : v(in), comparator(cmp) {
    heapify();
  };

  template<typename Type>
  static void HeapSort(std::vector<Type>& v, const Cmp& cmp = Cmp()) {
    Heap<T, Cmp> heap(v, cmp);
    for (long i = v.size() - 1; i > 0; --i) {
      std::swap(v[0], v[i]);
      heap.downheap(0, i);
    }
  }

private:
  std::vector<T>& v;
  const Cmp& comparator;

  void heapify() {
    long begin = v.size() / 2 - 1;
    for (long i = begin; i >= 0; --i) {
      downheap(i, v.size());
    }
  }

  long higherValueIndex(long left, long right) const {
    if (right == -1) {
      return left;
    }
    return comparator(v[right], v[left]) ? left : right;
  }

  long leftChildIndex(long i) const {
    return 2 * i + 1;
  }

  long rightChildIndex(long i, long to) const {
    long idx = 2 * i + 2;
    return idx < to ? idx : -1;
  }

  long parent(long i) const {
    return (i % 2 == 1) ? i / 2 : i / 2 - 1;
  }

  bool isLeaf(long i, long to) const {
    return i > to / 2 - 1;
  }

  void downheap(long i, long to) {
    if (to == 1) {
      return;
    }
    do {
      long left = leftChildIndex(i);
      long right = rightChildIndex(i, to);
      long higher_child = higherValueIndex(left, right);
      if (comparator(v[i], v[higher_child])) {
        std::swap(v[higher_child], v[i]);
        i = higher_child;
      } else {
        break;
      }
    } while (!isLeaf(i, to));
  }

};
