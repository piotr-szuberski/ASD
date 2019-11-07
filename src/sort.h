#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#include <numeric>
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

  template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void SelectionSort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
    for (Iter i = end - 1; std::distance(begin, i) > 0; --i) {
      Iter selectedElem = std::min_element(begin, i + 1, cmp);
      std::swap(*selectedElem, *i);
    }
  }

 template<
    typename Iter,
    typename Cmp = std::greater<typename std::iterator_traits<Iter>::value_type>>
  static void MergeSort(Iter begin, Iter end, const Cmp& cmp = Cmp()) {
    long length = std::distance(begin, end);
    if (length < 6) {
      InsertionSort(begin, end, cmp);
      return;
    }
    Iter mid = std::next(begin, length / 2);
    MergeSort(begin, mid, cmp);
    MergeSort(mid, end, cmp);
    Merge(begin, mid, end, cmp);
  }

 template<typename Iter, typename IterValueType = typename std::iterator_traits<Iter>::value_type>
  static void CountSort(Iter begin, Iter end, const IterValueType& m) {
    long length = std::distance(begin, end);
    std::vector<IterValueType> v(m);
    for (Iter i = begin; i != end; ++i) {
      v[*i] += 1;
    }
    for (size_t i = 1; i < v.size(); ++i) {
      v[i] += v[i - 1];
    }
    std::vector<IterValueType> tmp(length);
    for (Iter i = end - 1; i != begin - 1; --i) {
      tmp[--v[*i]] = std::move(*i);
    }
    Iter k = begin;
    for (size_t i = 0; i < tmp.size(); ++i) {
      *k = std::move(tmp[i]);
      ++k;
    }
  }

static void LexicographicEqualWordsSort(std::vector<std::string>& v, long k) {
  std::vector<int> alphabet(std::numeric_limits<std::string::value_type>::max());
  std::vector<int> positions(v.size());
  std::iota(positions.begin(), positions.end(), 0);
  
  for (long phase = k - 1; phase >= 0; --phase) {
    std::vector<int> tmp(v.size());
    alphabet.assign(alphabet.size(), 0);
    for (size_t i = 0; i < v.size(); ++i) {
      alphabet[v[positions[i]][phase]] += 1;
    }
    for (size_t i = 1; i < alphabet.size(); ++i) {
      alphabet[i] += alphabet[i - 1];
    }
    for (long i = positions.size() - 1; i >= 0; --i) {
      tmp[--alphabet[v[positions[i]][phase]]] = positions[i];
    }
    positions = std::move(tmp);
  }
  std::vector<std::string> sorted(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    sorted[i] = std::move(v[positions[i]]);
  }
  v = std::move(sorted);
}

private:
  template<typename Iter, typename Cmp>
  static void HInsertionSort(Iter begin, Iter end, long h, const Cmp& cmp) {
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

  template<typename Iter, typename Cmp>
  static void Merge(Iter begin, Iter mid, Iter end, const Cmp& cmp) {
    using IterValueType = typename std::iterator_traits<Iter>::value_type;
    std::vector<IterValueType> tmp(std::distance(begin, end));
    Iter left = begin, right = mid, tmpIter = tmp.begin();
    while (left != mid && right != end) {
      if (cmp(*right, *left)) {
        *tmpIter = std::move(*left);
        ++left;
      } else {
        *tmpIter = std::move(*right);
        ++right;
      }
      ++tmpIter;
    }
    while (left != mid) {
      *tmpIter = std::move(*left);
      ++left;
      ++tmpIter++;
    }
    while (right != end) {
      *tmpIter = std::move(*right);
      ++right;
      ++tmpIter++;
    }
    for (IterValueType& value : tmp) {
      *begin = std::move(value);
      ++begin;
    }
  }

  static size_t longest_string();

};

