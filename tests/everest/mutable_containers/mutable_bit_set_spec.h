#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_containers/mutable_bit_set.h>
#include <everest/mutable_containers/bit_set/all_traits.h>

namespace everest {

void MutableBitSetSpecification() {
  Describe("A MutableBitSet type", []() {
    Describe("That has been allocated with the default size", []() {
      auto bits = MutableBitSet();
      It("Should render 32 0 bits when passed through Shows()", [&]() {
        auto expected = String("MutableBitSet(00000000000000000000000000000000)");
        auto result   = Show(bits);
        AssertEquals(expected, result);
      });
      It("Should return 32 when passed through Length()", [&]() {
        auto expected = (size_t) 32;
        auto result   = Length(bits);
        AssertEquals(expected, result);
      });
      It("Should return true when passed through IsEmpty()", [&]() {
        auto result = IsEmpty(bits);
        AssertTrue(result);
      });
      It("Should return true when called with Contains(false)", [&]() {
        auto result = Contains(false, bits);
        AssertTrue(result);
      });
      It("Should return false when called with Contains(true)", [&]() {
        auto result = Contains(true, bits);
        AssertFalse(result);
      });
      Describe("And has had the low bit set to 1", [&]() {
        It("Should render 31 0 bits and a 1 1 bit when passed through Shows()", [&]() {
          auto expected = String("MutableBitSet(00000000000000000000000000000001)");
          auto result   = Show(bits.SetInPlace(0, true));
          AssertEquals(expected, result);
        });
      });
      Describe("And has had the low bit set to 0 and the high bit set to 1", [&]() {
        It("Should render 1 1 bit and 31 0 bits passed through Shows()", [&]() {
          auto expected = String("MutableBitSet(10000000000000000000000000000000)");
          auto result   = Show(bits.SetInPlace(0, false).SetInPlace(31, true));
          AssertEquals(expected, result);
        });
      });
    });
    Describe("That has been allocated with an off size", []() {
      auto bits = MutableBitSet(6);
      It("Should render 6 0 bits when passed through Shows()", [&]() {
        auto expected = String("MutableBitSet(000000)");
        auto result   = Show(bits);
        AssertEquals(expected, result);
      });
      It("Should return 6 when passed through Length()", [&]() {
        auto expected = (size_t) 6;
        auto result   = Length(bits);
        AssertEquals(expected, result);
      });
      It("Should return true when passed through IsEmpty()", [&]() {
        auto result = IsEmpty(bits);
        AssertTrue(result);
      });
      It("Should return true when called with Contains(false)", [&]() {
        auto result = Contains(false, bits);
        AssertTrue(result);
      });
      It("Should return false when called with Contains(true)", [&]() {
        auto result = Contains(true, bits);
        AssertFalse(result);
      });
      Describe("And has had the low bit set to 1", [&]() {
        It("Should render 5 0 bits and a 1 1 bit when passed through Shows()", [&]() {
          auto expected = String("MutableBitSet(000001)");
          auto result   = Show(bits.SetInPlace(0, true));
          AssertEquals(expected, result);
        });
      });
      Describe("And has had the low bit set to 0 and the high bit set to 1", [&]() {
        It("Should render 1 1 bit and 5 0 bits passed through Shows()", [&]() {
          auto expected = String("MutableBitSet(100000)");
          auto result   = Show(bits.SetInPlace(0, false).SetInPlace(5, true));
          AssertEquals(expected, result);
        });
      });
    });
  });
}
}