#pragma once
#include <vector>

/*
  greater - max heap
  less - min heap
 */
template<typename T, typename Cmp = std::greater<T>>
class Heap {

private:
  std::vector<T> v;
  const Cmp& comparator;

  std::vector<T>& getV() {
    return v;
  }

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
    return comparator(v[left], v[right]) ? left : right;
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
      if (comparator(v[higher_child], v[i])) {
        std::swap(v[higher_child], v[i]);
        i = higher_child;
      } else {
        break;
      }
    } while (!isLeaf(i, to));
  }

  void sort() {
    for (long i = v.size() - 1; i > 0; --i) {
      std::swap(v[0], v[i]);
      downheap(0, i);
    }
  }

public:

  Heap(const Cmp& cmp = Cmp()): comparator(cmp) {};

  Heap(const std::vector<T>& in, const Cmp& cmp = Cmp()): v(in), comparator(cmp) {
    heapify();
  };

  Heap(std::vector<T>&& in, const Cmp& cmp = Cmp()): v(std::move(in)), comparator(cmp) {
    heapify();
  };

  /* less - descending, greater - ascending */
  static void HeapSort(std::vector<T>& v, const Cmp& cmp = Cmp()) {
    Heap<T, Cmp> heap(std::move(v), cmp);
    heap.sort();
    v = std::move(heap.getV());
  }

};
