#pragma once

#include <limits>
#include <everest/test/bdd.h>
#include <everest/types/int32.h>
#include <everest/types/int32/all_traits.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void Int32Specification() {
  auto zero_n    = Int32(0);
  auto fortytwo  = Int32(42);
  auto twentyone = Int32(21);
  auto six       = Int32(6);
  auto three     = Int32(3);
  auto ten       = Int32(10);
  auto five      = Int32(5);
  auto nine      = Int32(9);
  auto twelve    = Int32(12);
  Describe("A type int32", [=]() {
    It("should have a zero value of zero_n", [=]() {
      AssertEquals(zero_n, Zero<Int32>());
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
      AssertEquals<int32_t>(-fortytwo.Value(), Negate(fortytwo).Value());
    });
    It("should have a min value accessible via the MinValue() function", [=]() {
      AssertEquals(std::numeric_limits<int32_t>::min(), MinValue<Int32>().Value());
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      AssertEquals(std::numeric_limits<int32_t>::max(), MaxValue<Int32>().Value());
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
      AssertEquals<int32_t>(fortytwo.Value() & twelve.Value(), BinaryAnd(fortytwo, twelve).Value());
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      AssertEquals<int32_t>(fortytwo.Value() | twelve.Value(), BinaryOr(fortytwo, twelve).Value());
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      AssertEquals<int32_t>(fortytwo.Value() ^ twelve.Value(), BinaryXor(fortytwo, twelve).Value());
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("42"), Show(fortytwo));
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("-42"), Show(fortytwo.Negate()));
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      auto expected = String("-42");
      auto result = Show((int32_t) -fortytwo.Value());
      auto failure = "Show(-42) did not return '-42'";
      AssertEquals(failure, expected, result);
    });
    It("should convert to the correct hex value when called with ToHex()", [=]() {
      auto expected = String("42424242");
      auto result   = ToHex((int32_t) 1111638594);
      auto failure  = "ToHex(1111638594) did not return '42424242'";
      AssertEquals(failure, expected, result);
    });
  });
}

}
