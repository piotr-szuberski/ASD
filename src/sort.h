#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#include <numeric>
#include <queue>
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

template<typename Word>
static void LexicographicEqualWordsSort(std::vector<Word>& v, long k) {
  long maxValue = getMaxFromWords(v);

  std::vector<long> alphabet(maxValue + 1);
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
  std::vector<Word> sorted(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    sorted[i] = std::move(v[positions[i]]);
  }
  v = std::move(sorted);
}

template<typename Word>
static void LexicographicSort(std::vector<Word>& v) {
  long maxValue = getMaxFromWords(v);
  // Get the size of the longest string
  size_t maxLength = std::max_element(v.begin(), v.end(),
      [] (const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
      }
  )->size();
  // First: value, second: index
  std::vector<std::vector<long>> indexes;
  for (const auto& val : v) {
    for (size_t i = 0; i < val.size(); ++i) {
      std::vector<long> x{static_cast<long>(val[i]), static_cast<long>(i)};
      indexes.emplace_back(std::move(x));
    }
  }
  // Sort by values and indexes
  Sort::LexicographicEqualWordsSort(indexes, 2);

  // Create structure that tells what alphabet's values at which index are used
  std::vector<std::vector<long>> alphabet(maxValue + 1);
  std::vector<long> previous = std::vector{-1L, -1L};
  for (const std::vector<long>& i: indexes) {
    if (previous == static_cast<std::vector<long>>(i)) {
      continue;
    }
    previous = static_cast<std::vector<long>>(i);
    alphabet[i[1]].push_back(i[0]);
  }
  
  // Vector of queues with index equal to word's length
  std::vector<std::vector<long>> lengthsList(maxLength + 1);
  for (size_t i = 0; i < v.size(); ++i) {
    lengthsList[v.size()].push_back(static_cast<long>(i));
  }

  std::deque<long> a;
  std::vector<std::queue<long>> Q(maxValue + 1);
  for (size_t i = maxLength - 1; i >= 1; --i) {
    std::vector<long>& currentLengths = lengthsList[i];
    for (size_t j = currentLengths.size(); j >= 1; --j) {
      a.push_front(currentLengths[j - 1]);
    }
    while (!a.empty()) {
      Q[v[a.front()][i - 1]].push(a.front());
      a.pop_front();
    }
    for (const long j: alphabet[i - 1]) {
      while (!Q[j].empty()) {
        a.push_back(Q[j].front());
        Q[j].pop();
      }
    }
  }
  std::vector<Word> sorted(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    sorted[i] = std::move(v[a.front()]);
    a.pop_front();
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
  
  template<typename Word>
  static long getMaxFromWords(const std::vector<Word>& v) {
    long maxValue = 0;
    for (const Word& w: v) {
      maxValue = std::max(static_cast<long>(*std::max_element(w.begin(), w.end())), maxValue);
    }
    return maxValue;
  }

};

