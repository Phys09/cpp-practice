#include <array>
#include <chrono>
#include <cstddef>
#include <exception>
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

/*
    Base
   /   \
 D1    D2
   \  /  \
    E1    E2
      \  /
       MD
 */

struct Base {
  void base_fn() { std::println("base_fn"); }
};

struct D1 : public Base {};
struct D2 : public Base {};

struct E1 : public D1, public D2 {};
struct E2 : public D2 {};

struct MD : public E1, public E2 {};

int main() {
  E1 e1{};
  e1.D1::base_fn();
  MD md{};

  /**
    1. Ambiguous conversion from derived class 'MD' to base class 'E1::D2':
       struct MD -> E1 -> D2
       struct MD -> E2 -> D2 [ambiguous_derived_to_base_conv]
  md.E1::D2::base_fn();
  */
  md.E1::D1::base_fn(); // unambiguous enough since getting to E1::D1 == D1 has
                        // only one path
  md.E2::base_fn(); // same
  // md.E1::D1::Base::base_fn(); // But this is not, since it still refers to Base

  /**
    1. Ambiguous conversion from derived class 'MD' to base class 'E1::D2::Base':
       struct MD -> E1 -> D1 -> Base
       struct MD -> E1 -> D2 -> Base
       struct MD -> E2 -> D2 -> Base [ambiguous_derived_to_base_conv]
  md.E1::D2::Base::base_fn();
  */
}
