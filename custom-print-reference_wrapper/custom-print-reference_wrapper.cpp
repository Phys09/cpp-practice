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
    std::string temp =
        std::format("{}{}, {}{}", "{", item.count, item.name, "}");
    return std::formatter<std::string_view>::format(temp, ctx);
  }
};

struct Solution {
public:
  std::string reverse_words(const std::span<std::string> words) {}
};

void print_items(const std::span<Item> items) {
  for (const auto &i : items) {
    std::print("{} ", i);
  }
  std::println();
}

void print_items3(std::span<std::reference_wrapper<Item>> items) {

  for (const auto &i : items) {
    std::cout << std::string((Item&)i) << " ";
  }
  std::println();
}

int main() {
  std::vector<std::string> words1{"  hello world "};  // world hello
  std::vector<std::string> words2{"the sky is blue"}; // blue is sky the

  std::vector<Item> items1{{.count = 1, .name = "first:items1"},
                           {.count = 2, .name = "second:items1"},
                           {.count = 3, .name = "third:items1"}};
  std::vector<Item> items2{items1.begin(), items1.begin() + 2};
  std::vector<std::reference_wrapper<Item>> items3{items1.begin(),
                                                   items1.begin() + 2};

  std::print("items1 before modifying items2: ");
  print_items(items1);
  std::print("items2 before modifying items2: ");
  print_items(items2);
  std::print("items3 before modifying items3: ");
  print_items3(items3);

  items1[0].count = 222;
  items2[0].count = 222;

  std::print("items1 after modifying items2: ");
  print_items(items1);
  std::print("items2 after modifying items2: ");
  print_items(items2);
  std::print("items3 after modifying items3: ");
  print_items3(items3);
}
