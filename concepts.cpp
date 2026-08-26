#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <flat_map>
#include <map>
#include <print>
#include <random>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
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

struct BaseWidget {
public:
  virtual ~BaseWidget() = 0;
};

struct TextWidget final : BaseWidget {
public:
  TextWidget(std::string_view sv) {
    std::println("Imgui::BeginText({})", sv.data());
  }
  TextWidget(const TextWidget &other) = delete;
  TextWidget &operator=(const TextWidget &other) = delete;
  TextWidget(const TextWidget &&other) = delete;
  TextWidget &operator=(const TextWidget &&other) = delete;
  ~TextWidget() override { std::println("~TextWidget"); }
};

template <typename T>
  requires std::is_arithmetic_v<T> and std::is_trivially_copyable_v<T>
void print_distribution(const std::map<T, T> &dist) {
  for (const auto &[k, v] : dist) {
    std::println("{0:3}: {1}", k, std::string(v / 1, '*'));
  }
}

template <typename T>
  requires std::is_trivial_v<T> and requires(T boollike) {
    { boollike } -> std::convertible_to<bool>;
    { not boollike } -> std::convertible_to<bool>;
  }
void toggle(T &b) {
  b = not b;
}

struct SwitchLike {
  bool value = 0;
  std::string info;
};

int main() {
  auto rd = std::random_device();
  auto generator = std::mt19937(rd());
  auto dice = std::uniform_int_distribution(1, 20);

  constexpr int num_rolls = 1000;
  auto roll_distribution = std::map<int, int>{};

  for (size_t _{}; _ < num_rolls; ++_) {
    roll_distribution[dice(generator)]++;
  }

  std::println("{}", 777);

  print_distribution(roll_distribution);
}
