#include <iostream>
#include <functional>
#include <string>

#include "types/int.h"

#include "containers/option.h"
#include "containers/monoids/max.h"
#include "containers/monoids/min.h"

int main(int argc, char **argv) {

  std::cout << "== Basic" << std::endl
            << show(add(zero<int>(), max_value<int>())) << std::endl
            << show(map<option, int, int>(option<int>(42), [](const int& n) { return n * 2; })) << std::endl
            << std::endl;

  int a = 6;
  int b = 4;

  std::cout << "== Int" << std::endl
            << "bounded min: " << min_value<int>() << std::endl
            << "bounded max: " << max_value<int>() << std::endl
            << "add: " << add(a, b) << std::endl
            << "subtract: " << subtract(a, b) << std::endl
            << "multiply: " << multiply(a, b) << std::endl
            << "divide: " << divide(a, b) << std::endl
            << "remainder: " << remainder(a, b) << std::endl
            << "zero: " << zero<int>() << std::endl
            << "one: " << one<int>() << std::endl
            // << "negate: " << negate(a) << std::endl
            << "monoid: " << add(a, zero<int>()) << std::endl
            << "cmp max: " << max(a, b) << std::endl
            << "cmp min: " << min(a, b) << std::endl
            << std::endl;

 std::cout << "== Monoid Max" << std::endl;
 auto a1 = max_monoid<int>(3);
 auto a2 = max_monoid<int>(9);
 auto a3 = max_monoid<int>(2);

 std::cout << "max_monoid(3) + max_monoid(9) + max_monoid(2) = "
           << show(add(a1, add(a2, a3))) << std::endl
           << std::endl;

 std::cout << "== Monoid min" << std::endl;
 auto b1 = min_monoid<int>(3);
 auto b2 = min_monoid<int>(9);
 auto b3 = min_monoid<int>(2);

 std::cout << "min_monoid(3) + min_monoid(9) + min_monoid(2) = "
           << show(add(b1, add(b2, b3))) << std::endl
           << std::endl;

 auto some1 = option<int>(6);
 auto some2 = option<int>(3);
 auto some3 = option<int>(6);
 auto none1 = make_none<int>();

 std::cout << "== Option" << std::endl
           << "print some: " << show(some1) << std::endl
           << "print none: " << show(none1) << std::endl
           << "some(6) == some(3): " << equals(some1, some2) << std::endl
           << "some(6) == some(6): " << equals(some1, some3) << std::endl
           << "none == some(6): " << equals(none1, some1) << std::endl
           << "some(6).length(): " << length(some1) << std::endl
           << "none.length(): " << length(none1) << std::endl
           << "some(6).is_empty(): " << is_empty(some1) << std::endl
           << "none.is_empty(): " << is_empty(none1) << std::endl
           << std::endl;
 
}
