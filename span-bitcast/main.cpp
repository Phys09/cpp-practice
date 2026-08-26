#include <array>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <print>
#include <span>
#include <vector>

struct Point {
  int x, y;
};
/**
 * https://simplifycpp.org/books/minibooklet/mini_booklet_Memory_Management_in_Modern_CPP.pdf
 * 2.3 Implement a small function that accepts a std::span<std::byte> and safely
 * interprets it as a Point if the size matches
 */
std::optional<Point> ex2_3(std::span<std::byte> bytes) {
  if (bytes.size_bytes() != sizeof(Point)) {
    return std::nullopt;
  }

  Point pt;
  memcpy(&pt, bytes.data(), bytes.size());
  return pt;
}

int main(int argc, char *argv[]) {
  std::println("Running program:");
  auto raw_data = std::vector<std::byte>(
      {std::byte{12}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{21},
       std::byte{0}, std::byte{0}, std::byte{0}});

  auto maybe_point = ex2_3(raw_data);

  if (not maybe_point) {
    std::println("maybe_point has no value");
    std::exit(-1);
  }

  std::println("maybe_point has a value: x = {}, y = {}", maybe_point->x,
               maybe_point->y);

  for (const auto &byte : raw_data) {
    std::print("{}", (unsigned char)byte);
  }
  return 0;
}
