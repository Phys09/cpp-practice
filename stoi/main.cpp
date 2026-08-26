#include <cassert>
#include <cmath>
#include <ranges>
#include <string>
#include <string_view>
int my_stoi(std::string_view sv) {
  int answer = 0;
  // converting a character to its number is same as subtracting '0' from it
  // '0' -> 0
  // '1' -> 1
  //
  // c - '0';
  auto reversed_sv = sv | std::ranges::views::reverse;
  for (const auto& [exponent, character] : std::views::enumerate(reversed_sv)) {
    answer += std::pow(10, exponent) * static_cast<int>(character - '0');
  }
  return answer;
}
int main (int argc, char *argv[]) {
  std::string s = "1738";
  const char *c_s = "1738";
  const char c_array[] = {'1','7','3','8','\0'};



  assert(my_stoi(s) == 1738 and "std::string to int works");
  assert(my_stoi(c_s) == 1738 and "c_str to int works");
  assert(my_stoi(c_array) == 1738 and "c_array to int works");
  return 0;
}
