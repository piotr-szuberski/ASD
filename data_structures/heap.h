#pragma once
#include <vector>

template<typename T, typename Cmp>
class Heap {
  private:
  std::vector<T>& v;
  long size;
  Cmp comparator;

  void heapify() {
    long begin = v.size() / 2 - 1;
    for (long i = begin; i >= 0; --i) {
      downheap(i);
    }
  }

  long higherValueIndex(long left, long right) const {
    if (right == -1) {
      return left;
    }
    const T& left_val = v[left];
    const T& right_val = v[right];
    return comparator(v[left], v[right]) ? left : right;
  }

  long leftChildIndex(long i) const {
    return 2 * i + 1;
  }

  long rightChildIndex(long i) const {
    long idx = 2 * i + 2;
    return idx < size ? idx : -1;
  }

  long parent(long i) const {
    return (i % 2 == 1) ? i / 2 : i / 2 - 1;
  }

  bool isLeaf(long i) const {
    return i > size / 2 - 1;
  }

  public:
  Heap(std::vector<T>& in, Cmp cmp) : v(in), comparator(cmp), size(in.size()) {
    heapify();
  };

  void downheap(long i) {
    if (size == 1) {
      return;
    }
    do {
      long left = leftChildIndex(i);
      long right = rightChildIndex(i);
      long higher_child = higherValueIndex(left, right);
      if (comparator(v[higher_child], v[i])) {
        std::swap(v[higher_child], v[i]);
        i = higher_child;
      } else {
        break;
      }
    } while (!isLeaf(i));
  }

  void decreaseSize() {
      --size;
  }

};

