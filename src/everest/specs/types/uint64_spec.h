#pragma once

#include <limits>
#include <everest/test/bdd.h>
#include <everest/types/uint64.h>

namespace everest {

void Uint64Specification() {
  uint64_t zero_n    = 0;
  uint64_t fortytwo  = 42;
  uint64_t twentyone = 21;
  uint64_t six       = 6;
  uint64_t three     = 3;
  uint64_t ten       = 10;
  uint64_t five      = 5;
  uint64_t nine      = 9;
  uint64_t twelve    = 12;
  Describe("A type uint32", [=]() {
    It("should have a zero value of zero_n", [=]() {
      AssertEquals(zero_n, Zero<uint64_t>());
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
      AssertEquals<uint64_t>(-fortytwo, Negate(fortytwo));
    });
    It("should have a min value accessible via the MinValue() function", [=]() {
      AssertEquals(std::numeric_limits<uint64_t>::min(), MinValue<uint64_t>());
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      AssertEquals(std::numeric_limits<uint64_t>::max(), MaxValue<uint64_t>());
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
      AssertEquals<uint64_t>(fortytwo & twelve, BinaryAnd(fortytwo, twelve));
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      AssertEquals<uint64_t>(fortytwo | twelve, BinaryOr(fortytwo, twelve));
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      AssertEquals<uint64_t>(fortytwo ^ twelve, BinaryXor(fortytwo, twelve));
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("42"), Show(fortytwo));
    });
    It("should convert to the correct hex value when called with ToHex()", [=]() {
      auto expected = String("4242424242424242");
      auto result   = ToHex((uint64_t) 4774451407313060418);
      auto failure  = "ToHex(4774451407313060418) did not return '4242424242424242'";
      AssertEquals(failure, expected, result);
    });
  });
}

}

