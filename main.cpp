#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include <map>
#include <mutex>
#include <ostream>
#include <print>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

enum flag_t {
  flag0 = 0,
  flag1 = 1,
  flag2 = 2,
};

struct MyConfig {
  int magicnum;
  flag_t flag;
};

template <typename T>
  requires requires(T t) {
    { t } -> std::convertible_to<int>;
  }
void foo(T &t) {
  t = 2;
}

template <typename T>
  requires(std::is_integral_v<T>)
void f1(T &t) {
  t = 1;
}

template <typename T, typename U> std::pair<T, U> combine(T left, U right) noexcept { return std::pair{left, right}; }

template <typename T> struct remove_reference2 {
  using type = T;
};

template <typename T> struct remove_reference2<T &&> {
  using type = T;
};

template <typename T> struct remove_reference2<T &> {
  using type = T;
};

// First define our non-specialized class template
template <typename T> class Storage8 {
private:
  T m_array[8];

public:
  void set(int index, const T &value) { m_array[index] = value; }

  const T &get(int index) const { return m_array[index]; }
};

// Now define our specialized class template
template <>            // the following is a template class with no templated parameters
class Storage8<double> // we're specializing Storage8 for bool
{
  // What follows is just standard class implementation details

private:
  std::uint8_t m_data{};

public:
  // Don't worry about the details of the implementation of these functions
  void set(int index, bool value) {
    // Figure out which bit we're setting/unsetting
    // This will put a 1 in the bit we're interested in turning on/off
    auto mask{1 << index};

    if (value)         // If we're setting a bit
      m_data |= mask;  // use bitwise-or to turn that bit on
    else               // if we're turning a bit off
      m_data &= ~mask; // bitwise-and the inverse mask to turn that bit off
  }

  bool get(int index) {
    // Figure out which bit we're getting
    auto mask{1 << index};
    // bitwise-and to get the value of the bit we're interested in
    // Then implicit cast to boolean
    return (m_data & mask);
  }
};
template <typename T> class B {
public:
  void f() {} // Member of class B<T>
};
template <typename T> class D : public B<T> {
public:
  void g() {
    f(); // Bad (even though some compilers erroneously (temporarily?) accept it)
  }
};

// Same example as before
int main2() {
  // Define a Storage8 for integers (instantiates Storage8<T>, where T = int)
  Storage8<int> intStorage;

  for (int count{0}; count < 8; ++count) {
    intStorage.set(count, count);
  }

  for (int count{0}; count < 8; ++count) {
    std::cout << intStorage.get(count) << '\n';
  }

  // Define a Storage8 for bool  (instantiates Storage8<bool> specialization)
  Storage8<bool> boolStorage;

  for (int count{0}; count < 8; ++count) {
    boolStorage.set(count, count & 3);
  }

  std::cout << std::boolalpha;

  for (int count{0}; count < 8; ++count) {
    std::cout << boolStorage.get(count) << '\n';
  }

  return 0;
}

int main() {
  namespace rg = std::ranges;
  std::vector numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::vector arrows = {↕, ↕, ↕, ↕, ↕, ↕, ↕, ↕, ↕, ↕};
  std::vector arrows(10, std::string{"\u2195"});
  std::string formatted_arrows = std::format("{}", arrows);
  std::erase(formatted_arrows, '"');

  std::println("Shuffling numbers: {}", numbers);
  std::random_device rd;
  auto g = std::mt19937(rd());
  rg::shuffle(numbers, g);
  std::println("Shuffled List with indices: \n{}\n{}\n{}", numbers, formatted_arrows, indices);

  std::println("Trying to keep index parity after sorting numbers");

  rg::sort(indices, std::less{}, [&numbers](int n) { return numbers[n]; });
  rg::sort(numbers);
  std::println("After sort attempt: \n{}\n{}\n{}", numbers, formatted_arrows, indices);

  std::vector<std::vector<int>> triplets{};
  triplets.emplace_back(std::initializer_list<int>{1,2,3});
  std::println("{}", triplets);
}
