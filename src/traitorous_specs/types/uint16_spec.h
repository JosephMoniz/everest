#ifndef TRAITOROUS_UINT16_SPEC_H
#define TRAITOROUS_UINT16_SPEC_H

#include <limits>

#include "test/bdd.h"

#include "types/uint16.h"

namespace traitorous {

void uint16_specification() {
  uint16_t zero_n    = 0;
  uint16_t fortytwo  = 42;
  uint16_t twentyone = 21;
  uint16_t six       = 6;
  uint16_t three     = 3;
  uint16_t ten       = 10;
  uint16_t five      = 5;
  uint16_t nine      = 9;
  uint16_t twelve    = 12;
  describe("A type uint16", [=]() {
    it("should have a zero value of zero_n", [=]() {
      return Zero<uint16_t>() == zero_n;
    });
    it("should be addable via the Add() function", [=]() {
      return Add(twentyone, twentyone) == fortytwo;
    });
    it("should be subtractable via the Subtract() function", [=]() {
      return Subtract(six, three) == three;
    });
    it("should be multiplyable via the Multiply() function", [=]() {
      return Multiply(three, three) == nine;
    });
    it("should be divadable via the Divide() function", [=]() {
      return Divide(nine, three) == three;
    });
    it("should be able to get the remainder via the Remainder() function", [=]() {
      return Remainder(ten, five) == zero_n;
    });
    it("should have a min value accessible via the MinValue() function", [=]() {
      return MinValue<uint16_t>() == std::numeric_limits<uint16_t>::min();
    });
    it("should have a max value accessible via the MaxValue() function", [=]() {
      return MaxValue<uint16_t>() == std::numeric_limits<uint16_t>::max();
    });
    it("should return true when an equal values are passed through Equals()", [=]() {
      return Equals(fortytwo, fortytwo);
    });
    it("should return false when unequal values are passed through Equals()", [=]() {
      return !Equals(fortytwo, twelve);
    });
    it("should return LESS when a lesser value is passed through Compare()", [=]() {
      return Compare(twelve, fortytwo) == LESS;
    });
    it("should return EQUAL when an equal value is passed through Compare()", [=]() {
      return Compare(fortytwo, fortytwo) == EQUAL;
    });
    it("should return GREATER when a greater value is passed through Compare()", [=]() {
      return Compare(fortytwo, twelve) == GREATER;
    });
    it("should return itself when passed through Min() with a greater value", [=]() {
      return Min(twelve, fortytwo) == twelve;
    });
    it("should return the other value when passed through Min() with a lesser value", [=]() {
      return Min(fortytwo, twelve) == twelve;
    });
    it("should return itself when passed through Max() with a lesser value", [=]() {
      return Max(fortytwo, twelve) == fortytwo;
    });
    it("should return the other value when passed through Max() with a greater value", [=]() {
      return Max(twelve, fortytwo) == fortytwo;
    });
    it("should be bitwise andable via the BinaryAnd() function", [=]() {
      return BinaryAnd(fortytwo, twelve) == (fortytwo & twelve);
    });
    it("should be bitwise orable via the BinaryOr() function", [=]() {
      return BinaryOr(fortytwo, twelve) == (fortytwo | twelve);
    });
    it("should be bitwise xorable via the BinaryXor() function", [=]() {
      return BinaryXor(fortytwo, twelve) == (fortytwo ^ twelve);
    });
  });
}

}

#endif