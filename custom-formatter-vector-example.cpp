#include <format>
#include <print>
#include <string_view>
#include <vector>
template <typename T> struct std::formatter<std::vector<T>> : std::formatter<std::string_view> {
  constexpr auto parse(const auto &ctx) const { return ctx.begin(); }

  constexpr auto format(const std::vector<T> &vec, auto &ctx) const {
    auto out = ctx.out();
    std::format_to(out, "CUSTOM!: [");
    for (int i = 0; i < vec.size(); ++i) {
      if (i < vec.size() - 1) {
        out = std::format_to(out, "{},", vec[i]);
      } else {
        out = std::format_to(out, "{}", vec[i]);
      }
    }
    out = std::format_to(out, "]");
    return out;
  }
};

int main(int argc, char *argv[]) {
  std::vector<int> nums{1, 2, 3, 4};
  std::println("{}", nums);
  return 0;
}
