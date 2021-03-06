#pragma once

#include <limits>
#include <everest/test/bdd.h>
#include <everest/types/uint8.h>
#include <everest/types/uint8/all_traits.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void UInt8Specification() {
  auto zero_n    = UInt8(0);
  auto fortytwo  = UInt8(42);
  auto twentyone = UInt8(21);
  auto six       = UInt8(6);
  auto three     = UInt8(3);
  auto ten       = UInt8(10);
  auto five      = UInt8(5);
  auto nine      = UInt8(9);
  auto twelve    = UInt8(12);
  Describe("A type uint8", [=]() {
    It("should have a zero value of zero_n", [=]() {
      AssertEquals(zero_n, Zero<UInt8>());
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
      AssertEquals(std::numeric_limits<uint8_t>::min(), MinValue<uint8_t>());
    });
    It("should have a max value accessible via the MaxValue() function", [=]() {
      AssertEquals(std::numeric_limits<uint8_t>::max(), MaxValue<uint8_t>());
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
      AssertEquals<uint8_t>(fortytwo.Value() & twelve.Value(), BinaryAnd(fortytwo, twelve).Value());
    });
    It("should be bitwise orable via the BinaryOr() function", [=]() {
      AssertEquals<uint8_t>(fortytwo.Value() | twelve.Value(), BinaryOr(fortytwo, twelve).Value());
    });
    It("should be bitwise xorable via the BinaryXor() function", [=]() {
      AssertEquals<uint8_t>(fortytwo.Value() ^ twelve.Value(), BinaryXor(fortytwo, twelve).Value());
    });
    It("should serialize to the correct value when called with Show()", [=]() {
      AssertEquals(String("42"), Show(fortytwo));
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

