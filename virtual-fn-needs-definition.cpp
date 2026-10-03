#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <print>
#include <random>
#include <string>
#include <string_view>
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

struct Item {
public:
  Item(std::string_view name) : itemName_(name) {
    std::println("Item() constructor");
  }

  void observe_item() { std::println("{}", itemName_); }

  Item(Item &other) noexcept { std::println("copy constuctor"); }
  Item(Item &&other) noexcept { std::println("copy constuctor"); }

  Item &operator=(const Item &other) noexcept {
    std::println("copy assignment");
    return *this;
  }
  Item &operator=(const Item &&other) noexcept {
    std::println("move assignment");
    return *this;
  }

private:
  std::string itemName_;
};

struct AbstractAnimal {
public:
  virtual int non_pure() { return 0; }
  // ODR-used entity => definition must exist somewhere in program
  // 10.3 Virtual functions
  // 11 A virtual function declared in a class shall be defined, or declared
  // pure (10.4) in that class, or both; but no diagnostic is required (3.2).
  // virtual int non_pure(); // Linker error due to not being defined
  virtual void make_sound() = 0;

protected:
  AbstractAnimal(Item &item, std::string_view name)
      : item_(item), name_(name) {}

private:
  Item item_;
  std::string name_;
};

struct IRunnable {
  virtual void run() = 0;
};

struct Duck : public AbstractAnimal, public IRunnable {
public:
  Duck(Item item, std::string_view name) : AbstractAnimal{item, "DuckType"} {}
  void make_sound() override { std::println("Qucking"); }
  int non_pure() override {
    std::println("non_pure not required to be overridden???");
    return 77;
  }
  void run() override { std::println("Waddle"); }
};

int main() {
  Duck duck{Item("Shovel"), "Quax"};

  duck.run();
}
