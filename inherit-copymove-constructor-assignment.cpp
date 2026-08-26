#include <chrono>
#include <cstddef>
#include <iostream>
#include <map>
#include <print>
#include <random>
#include <string>
#include <type_traits>

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
  requires std::is_arithmetic_v<T> and std::is_trivially_copyable_v<T>
void print_distribution(const std::map<T, T> &dist) {
  for (const auto &[k, v] : dist) {
    std::println("{0:3}: {1}", k, std::string(v / 1, '*'));
  }
}

struct TestItem {
  bool state;

  TestItem(bool setstate) : state(setstate) {}

  explicit operator bool() { return state; }
};

struct Base {
  Base() = default;
  void do_something() { std::cout << "Base is doing something\n"; }
  // deny copy
  Base(const Base &other) = delete;
  Base &operator=(const Base &other) = delete;
  // deny move
  Base(Base &&other) noexcept = delete;
  Base &operator=(Base &&other) noexcept = delete;
};

struct Derived final : public Base {
  int value;
  Derived(int v) : value(v) {}
};

int main() {
  auto rd = std::random_device();
  auto generator = std::mt19937(rd());
  auto dice = std::uniform_int_distribution(1, 20);

  constexpr int num_rolls = 1000;
  auto roll_distribution = std::map<int, int>{};

  auto b = Base();
  auto d = Derived(0);
  auto d1 = Derived(1);
  d1 = d;      // implicitly-deleted copy assignment
  auto d2 = d; // implicitly-deleted copy constructor of 'Derived'
  
  d1 = std::move(d);
  auto d3 = std::move(d);

  std::println("{}", sizeof(b));
  std::println("{}", sizeof(d));

  for (size_t _{}; _ < num_rolls; ++_) {
    roll_distribution[dice(generator)]++;
  }

  std::println("{}", 777);

  print_distribution(roll_distribution);
}
