#include <iostream>
#include <limits>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ostream>
#include <print>
#include <ranges>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

struct A {
  int i = 0;
  friend std::ostream &operator<<(std::ostream &os, A &a);
};

struct B : public A {
  int b = 1;
};

struct X1 {
  int x1 = 1;

  X1() { std::println("X1 initialized with: {}", x1); }

  ~X1() { std::println("X1 being destroyed with value: {}", x1); }
};

struct X2 {
  int x2 = 2;

  X2() { std::println("X2 initialized with: {}", x2); }

  ~X2() { std::println("X2 being destroyed with value: {}", x2); }
};

struct X3 {
  int x3 = 3;

  X3() { std::println("X3 initialized with: {}", x3); }

  ~X3() { std::println("X3 being destroyed with value: {}", x3); }
};

struct X4 {
  int x4 = 4;

  X4() { std::println("X4 initialized with: {}", x4); }

  ~X4() { std::println("X4 being destroyed with value: {}", x4); }
};

struct MyPackage {
  X1 x1;
  X2 x2;
  X3 x3;
  X4 x4;

  MyPackage() { std::println("Creating a package of 4 items"); }

  ~MyPackage() { std::println("Starting destruction of MyPackage"); }
};

void consumer() { MyPackage mp{}; }
int main() {
  double max = std::numeric_limits<double>::max();
  double inf = std::numeric_limits<double>::infinity();

  std::println("Value of 'has infinity' for type 'double' on windows: {}", std::numeric_limits<double>::has_infinity);

  if (inf > max)
    std::cout << inf << " is greater than " << max << '\n';
}
