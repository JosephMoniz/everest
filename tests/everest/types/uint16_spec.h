#pragma once

#include <limits>
#include <everest/test/bdd.h>
#include <everest/types/uint16.h>
#include <everest/types/uint16/all_traits.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void UInt16Specification() {
  auto zero_n    = UInt16(0);
  auto fortytwo  = UInt16(42);
  auto twentyone = UInt16(21);
  auto six       = UInt16(6);
  auto three     = UInt16(3);
  auto ten       = UInt16(10);
  auto five      = UInt16(5);
  auto nine      = UInt16(9);
  auto twelve    = UInt16(12);
  Describe("A type uint16", [=]() {
    It("should have a zero value of zero_n", [=]() {
      AssertEquals(zero_n, Zero<UInt16>());
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
    It("should have a min value accessible via the MinValue() function", [=]() {
      AssertEquals(std::numeric_limits<uint16_t>::min(), MinValue<uint16_t>());
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      AssertEquals(std::numeric_limits<uint16_t>::max(), MaxValue<uint16_t>());
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
      AssertEquals<uint16_t>(fortytwo.Value() & twelve.Value(), BinaryAnd(fortytwo, twelve).Value());
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      AssertEquals<uint16_t>(fortytwo.Value() | twelve.Value(), BinaryOr(fortytwo, twelve).Value());
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      AssertEquals<uint16_t>(fortytwo.Value() ^ twelve.Value(), BinaryXor(fortytwo, twelve).Value());
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("42"), Show(fortytwo));
    });
    It("should convert to the correct hex value when called with ToHex()", [=]() {
      auto expected = String("1092");
      auto result   = ToHex((int16_t) 4242);
      auto failure  = "ToHex(4242) did not return '1092'";
      AssertEquals(failure, expected, result);
    });
  });
}

}
