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

struct Item {
  int count;
  std::string name;

  operator std::string() const { return std::to_string(count) + name; }
};

template <>
struct std::formatter<Item> : public std::formatter<std::string_view> {
  auto format(const Item &item, std::format_context &ctx) const {
    std::string temp = std::format("{{{}, {}}}", item.count, item.name);
    return std::formatter<std::string_view>::format(temp, ctx);
  }
};

int main() { Item item{.count = 22, .name = "Rock"}; }
