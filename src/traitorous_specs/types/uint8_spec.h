#ifndef TRAITOROUS_UINT8_SPEC_H
#define TRAITOROUS_UINT8_SPEC_H

#include <limits>

#include "test/bdd.h"

#include "types/uint8.h"

namespace traitorous {

void uint8_specification() {
  uint8_t zero_n    = 0;
  uint8_t fortytwo  = 42;
  uint8_t twentyone = 21;
  uint8_t six       = 6;
  uint8_t three     = 3;
  uint8_t ten       = 10;
  uint8_t five      = 5;
  uint8_t nine      = 9;
  uint8_t twelve    = 12;
  describe("A type uint8", [=]() {
    it("should have a zero value of zero_n", [=]() {
      return zero<uint8_t>() == zero_n;
    });
    it("should be addable via the add() function", [=]() {
      return add(twentyone, twentyone) == fortytwo;
    });
    it("should be subtractable via the subtract() function", [=]() {
      return subtract(six, three) == three;
    });
    it("should be multiplyable via the multiply() function", [=]() {
      return multiply(three, three) == nine;
    });
    it("should be divadable via the divide() function", [=]() {
      return divide(nine, three) == three;
    });
    it("should be able to get the remainder via the remainder() function", [=]() {
      return remainder(ten, five) == zero_n;
    });
    it("should have a min value accessible via the min_value() function", [=]() {
      return min_value<uint8_t>() == std::numeric_limits<uint8_t>::min();
    });
    it("should have a max value accessible via the max_value() function", [=]() {
      return max_value<uint8_t>() == std::numeric_limits<uint8_t>::max();
    });
    it("should return true when an equal values are passed through equals()", [=]() {
      return equals(fortytwo, fortytwo);
    });
    it("should return false when unequal values are passed through equals()", [=]() {
      return !equals(fortytwo, twelve);
    });
    it("should return LESS when a lesser value is passed through cmp()", [=]() {
      return cmp(twelve, fortytwo) == LESS;
    });
    it("should return EQUAL when an equal value is passed through cmp()", [=]() {
      return cmp(fortytwo, fortytwo) == EQUAL;
    });
    it("should return GREATER when a greater value is passed through cmp()", [=]() {
      return cmp(fortytwo, twelve) == GREATER;
    });
    it("should return itself when passed through min() with a greater value", [=]() {
      return min(twelve, fortytwo) == twelve;
    });
    it("should return the other value when passed through min() with a lesser value", [=]() {
      return min(fortytwo, twelve) == twelve;
    });
    it("should return itself when passed through max() with a lesser value", [=]() {
      return max(fortytwo, twelve) == fortytwo;
    });
    it("should return the other value when passed through max() with a greater value", [=]() {
      return max(twelve, fortytwo) == fortytwo;
    });
    it("should be bitwise andable via the b_and() function", [=]() {
      return b_and(fortytwo, twelve) == (fortytwo & twelve);
    });
    it("should be bitwise orable via the b_or() function", [=]() {
      return b_or(fortytwo, twelve) == (fortytwo | twelve);
    });
    it("should be bitwise xorable via the b_xor() function", [=]() {
      return b_xor(fortytwo, twelve) == (fortytwo ^ twelve);
    });
  });
}

}

#endif
