#include <iostream>
#include <functional>
#include <string>

#include "types/int.h"

#include "containers/option.h"
#include "containers/monoids/max.h"
#include "containers/monoids/min.h"

int main(int argc, char **argv) {

  std::cout << "== Basic" << std::endl;
  std::cout << show(add(zero<int>(), max_value<int>())) << std::endl;
  std::cout << show(map<option, int, int>(option<int>(42), [](const int& n) { return n * 2; })) << std::endl;
  std::cout << std::endl;

  int a = 6;
  int b = 4;

  std::cout << "=== Int" << std::endl;
  std::cout << "bounded min: " << min_value<int>() << std::endl;
  std::cout << "bounded max: " << max_value<int>() << std::endl;
  std::cout << "add: " << add(a, b) << std::endl;
  std::cout << "subtract: " << subtract(a, b) << std::endl;
  //std::cout << "multiply: " << multiply(a, b) << std::endl;
  //std::cout << "divide: " << divide(a, b) << std::endl;
  //std::cout << "remainder: " << remainder(a, b) << std::endl;
  std::cout << "zero: " << zero<int>() << std::endl;
  std::cout << "one: " << one<int>() << std::endl;
  //std::cout << "negate: " << negate(a) << std::endl;
  std::cout << "monoid: " << add(a, zero<int>()) << std::endl;
  std::cout << "cmp max: " << max(a, b) << std::endl;
  std::cout << "cmp min: " << min(a, b) << std::endl;
  std::cout << std::endl;

 std::cout << "== Monoid Max" << std::endl;
 auto a1 = max_monoid<int>(3);
 auto a2 = max_monoid<int>(9);
 auto a3 = max_monoid<int>(2);

 std::cout << "max_monoid(3) + max_monoid(9) + max_monoid(2) = ";
 std::cout << show(add(a1, add(a2, a3))) << std::endl;
 std::cout << std::endl;

 std::cout << "== Monoid min" << std::endl;
 auto b1 = min_monoid<int>(3);
 auto b2 = min_monoid<int>(9);
 auto b3 = min_monoid<int>(2);

 std::cout << "min_monoid(3) + min_monoid(9) + min_monoid(2) = ";
 std::cout << show(add(b1, add(b2, b3))) << std::endl;
 std::cout << std::endl;

  /*
  auto some1 = std::make_shared<Some<UInt>>(6);
  auto some2 = std::make_shared<Some<UInt>>(3);
  auto some3 = std::make_shared<Some<UInt>>(6);
  auto none  = std::make_shared<None<UInt>>();
  
  std::cout << "== Option" << std::endl;
  std::cout << "print some: " << some1->show() << std::endl;
  std::cout << "print none: " << none->show() << std::endl;
  std::cout << "Some(6) == Some(3): " << some1->equals(some2) << std::endl;
  std::cout << "Some(6) == Some(6): " << some1->equals(some3) << std::endl;
  std::cout << "Some(6) == None: " << some1->equals(none) << std::endl;
  std::cout << "None == Some(6): " << none->equals(some1) << std::endl;
  std::cout << "Some(6).length(): " << some1->length()->show() << std::endl;
  std::cout << "None.length(): " << none->length()->show() << std::endl;
  std::cout << "Some(6).is_empty(): " << some1->is_empty() << std::endl;
  std::cout << "None.is_empty(): " << none->is_empty() << std::endl;
  std::cout << std::endl;


  return 0;
  */

}
