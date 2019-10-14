#include <vector>
#include <iostream>

template<typename T>
bool less(const T& t1, const T& t2) {
  return t1 < t2;
}

template<typename T>
bool greater(const T& t1, const T& t2) {
  return t1 > t2;
}

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

template<typename Iter, typename Cmp>
void insertion_sort(Iter begin, Iter end, Cmp comp) {
  h_insertion_sort(begin, end, 1, comp);
}

int main() {
  std::vector<int> v{};
  insertion_sort(v.begin(), v.end(), greater<int>);
  for (int i : v) {
    std::cout << i << std::endl;
  }
  insertion_sort(v.begin(), v.end(), less<int>);
  for (int i : v) {
    std::cout << i << std::endl;
  }
  return 0;
}
