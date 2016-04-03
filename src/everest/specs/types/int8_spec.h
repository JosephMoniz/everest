#pragma once

#include <limits>
#include <everest/test/bdd.h>
#include <everest/types/int8.h>

namespace everest {

void Int8Specification() {
  int8_t zero_n    = 0;
  int8_t fortytwo  = 42;
  int8_t twentyone = 21;
  int8_t six       = 6;
  int8_t three     = 3;
  int8_t ten       = 10;
  int8_t five      = 5;
  int8_t nine      = 9;
  int8_t twelve    = 12;
  Describe("A type int8", [=]() {
    It("should have a zero value of zero_n", [=]() {
      AssertEquals(zero_n, Zero<int8_t>());
    });
    It("should be addable via the Add() function", [=]() {
      AssertEquals(fortytwo, Add(twentyone, twentyone));
    });
    It("should be subtractable via the Subtract() function", [=]() {
      AssertEquals(three, Subtract(six, three));
    });
    It("should be multiplyable via the Multiply() function", [=]() {
      AssertEquals(nine, Multiply(three, three));
    });
    It("should be divadable via the Divide() function", [=]() {
      AssertEquals(three, Divide(nine, three));
    });
    It("should be able to get the remainder via the Remainder() function", [=]() {
      AssertEquals(zero_n, Remainder(ten, five));
    });
    It("should be negatable via the Negate() function", [=]() {
      AssertEquals<int8_t>(-fortytwo, Negate(fortytwo));
    });
    It("should have a min value accessible via the MinValue() function", [=]() {
      AssertEquals(std::numeric_limits<int8_t>::min(), MinValue<int8_t>());
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      AssertEquals(std::numeric_limits<int8_t>::max(), MaxValue<int8_t>());
    });
    It("should return true when an equal values are passed through Equals()", [=]() {
      AssertTrue(Equals(fortytwo, fortytwo));
    });
    It("should return false when unequal values are passed through Equals()", [=]() {
      AssertFalse(Equals(fortytwo, twelve));
    });
    It("should return LESS when a lesser value is passed through Compare()", [=]() {
      AssertEquals(Ordering::LESS, Compare(twelve, fortytwo));
    });
    It("should return EQUAL when an equal value is passed through Compare()", [=]() {
      AssertEquals(Ordering::EQUAL, Compare(fortytwo, fortytwo));
    });
    It("should return GREATER when a greater value is passed through Compare()", [=]() {
      AssertEquals(Ordering::GREATER, Compare(fortytwo, twelve));
    });
    It("should return itself when passed through Min() with a greater value", [=]() {
      AssertEquals(twelve, Min(twelve, fortytwo));
    });
    It("should return the other value when passed through Min() with a lesser value", [=]() {
      AssertEquals(twelve, Min(fortytwo, twelve));
    });
    It("should return itself when passed through Max() with a lesser value", [=]() {
      AssertEquals(fortytwo, Max(fortytwo, twelve));
    });
    It("should return the other value when passed through Max() with a greater value", [=]() {
      AssertEquals(fortytwo, Max(twelve, fortytwo));
    });
    It("should be bitwise andable via the BinaryAnd() function", [=]() {
      AssertEquals<int8_t>(fortytwo & twelve, BinaryAnd(fortytwo, twelve));
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      AssertEquals<int8_t>(fortytwo | twelve, BinaryOr(fortytwo, twelve));
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      AssertEquals<int8_t>(fortytwo ^ twelve, BinaryXor(fortytwo, twelve));
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("42"), Show(fortytwo));
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      auto expected = String("-42");
      auto result   = Show((int8_t) -fortytwo);
      auto failure  = "Show(-42) did not return '-42'";
      AssertEquals(failure, expected, result);
    });
    It("should convert to the correct hex value when called with ToHex()", [=]() {
      auto expected = String("2a");
      auto result   = ToHex(fortytwo);
      auto failure  = "ToHex(42) did not return '2a'";
      AssertEquals(failure, expected, result);
    });
  });
}

}
