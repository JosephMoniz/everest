#pragma once

#include <everest/test/bdd.h>
#include <everest/types/bool.h>
#include <everest/types/bool/all_traits.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void BoolSpecification() {
  Describe("A type Bool", []() {
    It("should have a zero value of false", []() {
      AssertFalse(Zero<Bool>().Value());
    });
    Describe("with a value of true", []() {
      It("should return true when passed to eq() w/ another boolean true", []() {
        AssertTrue(Equals(Bool(true), Bool(true)));
      });
      It("should return false when passed to eq() w/ a boolean false", []() {
        AssertFalse(Equals(Bool(true), Bool(false)));
      });
      It("should return true when compared for equality w/ another boolean true", []() {
        AssertTrue(Bool(true) == Bool(true));
      });
      It("should return false when compared for equality w/ a boolean false", []() {
        AssertFalse(Bool(true) == Bool(false));
      });
      It("should return EQUAL when Compare() called w/ a boolean true", []() {
        AssertEquals(Ordering::EQUAL, Compare(Bool(true), Bool(true)));
      });
      It("should return GREATER when Compare() called w/ a boolean false", []() {
        AssertEquals(Ordering::GREATER, Compare(Bool(true), Bool(false)));
      });
      It("should return 'true' when passed to Show()", []() {
        AssertEquals(String("true"), Show(Bool(true)));
      });
    });
    Describe("with a value of false", []() {
      It("should return false when passed to eq() w/ boolean true", []() {
        AssertFalse(Equals(Bool(false), Bool(true)));
      });
      It("should return true when passed to eq() w/ another boolean false", []() {
        AssertTrue(Equals(Bool(false), Bool(false)));
      });
      It("should return false when compared for equality w/ a boolean true", []() {
        AssertFalse(Bool(false) == Bool(true));
      });
      It("should return true when compared for equality w/ another boolean false", []() {
        AssertTrue(Bool(false) == Bool(false));
      });
      It("should return EQUAL when Compare() called w/ a boolean false", []() {
        AssertEquals(Ordering::EQUAL, Compare(Bool(false), Bool(false)));
      });
      It("should return LESS when Compare() called w/ a boolean true", []() {
        AssertEquals(Ordering::LESS, Compare(Bool(false), Bool(true)));
      });
      It("should return 'false' when passed to Show()", []() {
        AssertEquals(String("false"), Show(Bool(false)));
      });
    });
  });
}

}
