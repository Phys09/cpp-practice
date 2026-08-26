#include <algorithm>
#include <cassert>
#include <chrono>
#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <functional>
#include <future>
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
#include <system_error>
#include <tuple>
#include <type_traits>
#include <unordered_map>
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

#include <cstdio>
#include <cstdlib>
#include <new>

// no inline, required by [replacement.functions]/3
void *operator new(std::size_t sz) {
  std::printf("1) new(size_t), size = %zu\n", sz);
  if (sz == 0)
    ++sz; // avoid std::malloc(0) which may return nullptr on success

  if (void *ptr = std::malloc(sz))
    return ptr;

  throw std::bad_alloc{}; // required by [new.delete.single]/3
}

// no inline, required by [replacement.functions]/3
void *operator new[](std::size_t sz) {
  std::printf("2) new[](size_t), size = %zu\n", sz);
  if (sz == 0)
    ++sz; // avoid std::malloc(0) which may return nullptr on success

  if (void *ptr = std::malloc(sz))
    return ptr;

  throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void *ptr) noexcept {
  std::puts("3) delete(void*)");
  std::free(ptr);
}

void operator delete(void *ptr, std::size_t size) noexcept {
  std::printf("4) delete(void*, size_t), size = %zu\n", size);
  std::free(ptr);
}

void operator delete[](void *ptr) noexcept {
  std::puts("5) delete[](void* ptr)");
  std::free(ptr);
}

void operator delete[](void *ptr, std::size_t size) noexcept {
  std::printf("6) delete[](void*, size_t), size = %zu\n", size);
  std::free(ptr);
}

int main() {
  int *p1 = ::new int;
  delete p1;

  int *p2 = new int[10]; // guaranteed to call the replacement in C++11
  delete[] p2;
}
