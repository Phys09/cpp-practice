#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <ostream>
#include <print>
#include <random>
#include <ranges>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <vector>

struct Stopwatch {
private:
  std::chrono::steady_clock::time_point start;

public:
  Stopwatch() : start(std::chrono::steady_clock::now()) {}
  ~Stopwatch() {
    auto duration = std::chrono::steady_clock::now() - start;
    std::println("Duration: {}", duration);
  }
};

template <typename T>
concept not_ptr = not std::is_pointer_v<T>;

template <typename T>
concept not_integer = not std::is_integral_v<T>;

int *f() {}

template <typename T>
concept valid_type = not_ptr<T> and not_integer<T>;

valid_type auto f2() { return 2.0; }

template <typename T>
concept is_number = std::is_integral_v<T>;
void print_item(const is_number auto &item) { std::println("{}", item); }

int main() {
  int x[]{3, 2, 4, 5, 1, 7};
  valid_type auto item = f2();
  for (const auto &n : x | std::ranges::views::all) {
    std::println("Value in array: {}", n);
  }
}
