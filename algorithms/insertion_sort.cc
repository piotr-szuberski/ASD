#include <vector>
#include <iostream>

template<typename T, typename FuncType>
void h_insertion_sort(std::vector<T>& v, unsigned h, FuncType comp) {
  for (int i = h; i < v.size(); i += h) {
    int j = i - h, x = v[i];
    while (j >= 0 && comp(v[j], x)) {
      v[j + h] = v[j];
      j -= h;
    }
    v[j + h] = x;
  }
}

template<typename T, typename FuncType>
void insertion_sort(std::vector<T>& v, FuncType comp) {
  h_insertion_sort(v, 1, comp);
}

int main() {
  std::vector<int> v{0, 3, 2, 1};
  insertion_sort(v, [] (int a, int b) { return a > b; });
  for (int i : v) {
    std::cout << i << std::endl;
  }
  return 0;
}
