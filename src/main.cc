#include <functional>
#include <iostream>
#include <string>

#include "types/bool.h"
#include "types/int.h"
#include "types/string.h"

#include "containers/monoids/max.h"
#include "containers/monoids/min.h"
#include "containers/option.h"

using traitorous::add;
using traitorous::divide;
using traitorous::equals;
using traitorous::is_empty;
using traitorous::length;
using traitorous::make_none;
using traitorous::map;
using traitorous::max;
using traitorous::max_monoid;
using traitorous::max_value;
using traitorous::min;
using traitorous::min_monoid;
using traitorous::min_value;
using traitorous::multiply;
using traitorous::negate;
using traitorous::one;
using traitorous::option;
using traitorous::remainder;
using traitorous::show;
using traitorous::subtract;
using traitorous::zero;


int main(int argc, char **argv) {

  auto double_lambda = [](const auto& n) { return n * 2; };

  std::cout << "== Basic" << std::endl
            << show(add(zero<int>(), max_value<int>())) << std::endl
            << show(map<option, int, int>(double_lambda, option<int>(42))) << std::endl
            << show(option<bool>(option<bool>(true))) << std::endl
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
            << "negate: " << negate(a) << std::endl
            << "monoid: " << add(a, zero<int>()) << std::endl
            << "cmp max: " << max(a, b) << std::endl
            << "cmp min: " << min(a, b) << std::endl
            << std::endl;

  std::cout << "== Monoid Max" << std::endl;
  auto a1 = max_monoid<int>(3);
  auto a2 = max_monoid<int>(9);
  auto a3 = max_monoid<int>(2);

  std::cout << "max_monoid(3) + max_monoid(9) + max_monoid(2) = "
            << show(a1 + a2 + a3) << std::endl
            << std::endl;

  std::cout << "== Monoid min" << std::endl;
  auto b1 = min_monoid<int>(3);
  auto b2 = min_monoid<int>(9);
  auto b3 = min_monoid<int>(2);

  std::cout << "min_monoid(3) + min_monoid(9) + min_monoid(2) = "
            << show(b1 + b2 + b3) << std::endl
            << std::endl;

  auto some1 = option<int>(6);
  auto some2 = option<int>(3);
  auto some3 = option<int>(6);
  auto none1 = make_none<int>();

  std::cout << "== Option" << std::endl
            << "print some: " << show(some1) << std::endl
            << "print none: " << show(none1) << std::endl
            << "some(6) == some(3): " << show(equals(some1, some2)) << std::endl
            << "some(6) == some(6): " << show(equals(some1, some3)) << std::endl
            << "none == some(6): " << show(equals(none1, some1)) << std::endl
            << "length(some(6)): " << length(some1) << std::endl
            << "length(none): " << length(none1) << std::endl
            << "some(6).length(): " << some1.length() << std::endl
            << "none.length(): " << none1.length() << std::endl
            << "some(6).is_empty(): " << show(is_empty(some1)) << std::endl
            << "none.is_empty(): " << show(is_empty(none1)) << std::endl
            << std::endl;

  auto string1      = std::string("lol");
  auto string2      = std::string("wat");
  auto string3      = std::string("lol");
  auto empty_string = std::string("");

  std::cout << "== String" << std::endl
            << "string1.length(): " << length(string1) << std::endl
            << "empty_string.length(): " << length(empty_string) << std::endl
            << "string1.is_empty(): " << show(is_empty(string1)) << std::endl
            << "empty_string.is_empty(): " << show(is_empty(empty_string)) << std::endl
            << "string1 == string2: " << show(equals(string1, string2)) << std::endl
            << "string1 == string3: " << show(equals(string1, string3)) << std::endl
            << "zero<std::string>(): " << zero<std::string>() << std::endl
            << "add(string1, string2): " << add(string1, string2) << std::endl
            << std::endl;
 
}
