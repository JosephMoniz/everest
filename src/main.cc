#include <iostream>
#include <functional>
#include <limits>

#include "types/int.h"
#include "types/int8.h"
#include "types/int16.h"
#include "types/int32.h"
#include "types/int64.h"
#include "types/uint.h"
#include "types/uint8.h"
#include "types/uint16.h"
#include "types/uint32.h"
#include "types/uint64.h"

#include "containers/monoids/max.h"
#include "containers/monoids/min.h"

int main(int argc, char **argv) {

  auto a = std::make_shared<Int>(6);
  auto b = std::make_shared<Int>(4);

  std::cout << "=== Int" << std::endl;
  std::cout << "a: " << a->show() << std::endl;
  std::cout << "bounded min: " << a->min_value()->show() << std::endl;
  std::cout << "bounded max: " << a->max_value()->show() << std::endl;
  std::cout << "add: " << a->add(b)->show() << std::endl;
  std::cout << "subtract: " << a->subtract(b)->show() << std::endl;
  std::cout << "multiply: " << a->multiply(b)->show() << std::endl;
  std::cout << "divide: " << a->divide(b)->show() << std::endl;
  std::cout << "remainder: " << a->remainder(b)->show() << std::endl;
  std::cout << "zero: " << a->zero()->show() << std::endl;
  std::cout << "one: " << a->one()->show() << std::endl;
  std::cout << "negate: " << a->negate()->show() << std::endl;
  std::cout << "monoid: " << a->add(a->zero())->show() << std::endl;
  std::cout << "cmp max: " << a->max(b)->show() << std::endl;
  std::cout << "cmp min: " << a->min(b)->show() << std::endl;
  std::cout << std::endl;


  auto a1 = std::make_shared<Max<Int>>(3);
  auto b1 = std::make_shared<Max<Int>>(9);
  auto c1 = std::make_shared<Max<Int>>(4);

  std::cout << "=== Max Monoid" << std::endl;
  std::cout << "Max(3) + Max(9) + Max(2) = "
            << a1->add(b1)->add(c1)->show()
            << std::endl;
  std::cout << std::endl;


  auto a2 = std::make_shared<Min<Int>>(3);
  auto b2 = std::make_shared<Min<Int>>(9);
  auto c2 = std::make_shared<Min<Int>>(4);

  std::cout << "=== Min Monoid" << std::endl;
  std::cout << "Min(3) + Min(9) + Min(2) = "
            << a2->add(b2)->add(c2)->show()
            << std::endl;
  std::cout << std::endl;


  return 0;

}
