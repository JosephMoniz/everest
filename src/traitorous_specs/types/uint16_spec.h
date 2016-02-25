#ifndef TRAITOROUS_UINT16_SPEC_H
#define TRAITOROUS_UINT16_SPEC_H

#include <limits>

#include "test/bdd.h"

#include "types/uint16.h"

namespace traitorous {

void Uint16Specification() {
  uint16_t zero_n    = 0;
  uint16_t fortytwo  = 42;
  uint16_t twentyone = 21;
  uint16_t six       = 6;
  uint16_t three     = 3;
  uint16_t ten       = 10;
  uint16_t five      = 5;
  uint16_t nine      = 9;
  uint16_t twelve    = 12;
  Describe("A type uint16", [=]() {
    It("should have a zero value of zero_n", [=]() {
      return Zero<uint16_t>() == zero_n;
    });
    It("should be addable via the Add() function", [=]() {
      return Add(twentyone, twentyone) == fortytwo;
    });
    It("should be subtractable via the Subtract() function", [=]() {
      return Subtract(six, three) == three;
    });
    It("should be multiplyable via the Multiply() function", [=]() {
      return Multiply(three, three) == nine;
    });
    It("should be divadable via the Divide() function", [=]() {
      return Divide(nine, three) == three;
    });
    It("should be able to get the remainder via the Remainder() function", [=]() {
      return Remainder(ten, five) == zero_n;
    });
    It("should have a min value accessible via the MinValue() function", [=]() {
      return MinValue<uint16_t>() == std::numeric_limits<uint16_t>::min();
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      return MaxValue<uint16_t>() == std::numeric_limits<uint16_t>::max();
    });
    It("should return true when an equal values are passed through Equals()", [=]() {
      return Equals(fortytwo, fortytwo);
    });
    It("should return false when unequal values are passed through Equals()", [=]() {
      return !Equals(fortytwo, twelve);
    });
    It("should return LESS when a lesser value is passed through Compare()", [=]() {
      return Compare(twelve, fortytwo) == LESS;
    });
    It("should return EQUAL when an equal value is passed through Compare()", [=]() {
      return Compare(fortytwo, fortytwo) == EQUAL;
    });
    It("should return GREATER when a greater value is passed through Compare()", [=]() {
      return Compare(fortytwo, twelve) == GREATER;
    });
    It("should return itself when passed through Min() with a greater value", [=]() {
      return Min(twelve, fortytwo) == twelve;
    });
    It("should return the other value when passed through Min() with a lesser value", [=]() {
      return Min(fortytwo, twelve) == twelve;
    });
    It("should return itself when passed through Max() with a lesser value", [=]() {
      return Max(fortytwo, twelve) == fortytwo;
    });
    It("should return the other value when passed through Max() with a greater value", [=]() {
      return Max(twelve, fortytwo) == fortytwo;
    });
    It("should be bitwise andable via the BinaryAnd() function", [=]() {
      return BinaryAnd(fortytwo, twelve) == (fortytwo & twelve);
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      return BinaryOr(fortytwo, twelve) == (fortytwo | twelve);
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      return BinaryXor(fortytwo, twelve) == (fortytwo ^ twelve);
    });
  });
}

}

#endif