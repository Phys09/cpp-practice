#include <chrono>
#include <print>

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

int n = 22;
int arr[] = {1, 2, 3};
auto [a1, a2, a3] = arr;
// [[= 1]] void fn(int n);
enum Enum { A };
using Alias = int;
struct S {
  int mem;
};
template <auto> struct TCls {};
template <auto> void TFn();
template <auto> int TVar;
template <auto N> using TAlias = TCls<N>;
template <auto>
concept Concept = true;
namespace NS {}
namespace NSAlias = NS;

constexpr auto r_n = ^^n;

int main (int argc, char *argv[]) {
  return 0;
}
