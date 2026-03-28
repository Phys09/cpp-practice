#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
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

struct Item {
  int count;
  std::string name;

  operator std::string() const { return std::to_string(count) + name; }
  Item &operator=(const Item &other) = delete;
  Item &operator=(const Item &&other) {
    std::println("Move assignment operator");
    return *this;
  }
};

int main() {
  std::string s{"Smith, Jane, 99, Yu, Hello, 888"};
  std::istringstream iss(s);

  std::string buf{};
  while (std::getline(iss, buf, ',')) {
    std::cout << std::quoted(buf) << "\n";
  }
  return 0;
}
