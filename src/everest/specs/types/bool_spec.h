#pragma once

#include <everest/test/bdd.h>
#include <everest/types/bool.h>

namespace everest {

void BoolSpecification() {
  Describe("A type bool", []() {
    It("should have a zero value of false", []() {
      AssertFalse(Zero<bool>());
    });
    Describe("with a value of true", []() {
      It("should return true when passed to eq() w/ another boolean true", []() {
        AssertTrue(Equals(true, true));
      });
      It("should return false when passed to eq() w/ a boolean false", []() {
        AssertFalse(Equals(true, false));
      });
      It("should return true when compared for equality w/ another boolean true", []() {
        AssertTrue(true == true);
      });
      It("should return false when compared for equality w/ a boolean false", []() {
        AssertFalse(true == false);
      });
      It("should return EQUAL when Compare() called w/ a boolean true", []() {
        AssertEquals(Ordering::EQUAL, Compare(true, true));
      });
      It("should return GREATER when Compare() called w/ a boolean false", []() {
        AssertEquals(Ordering::GREATER, Compare(true, false));
      });
      It("should return 'true' when passed to Show()", []() {
        AssertEquals(String("true"), Show(true));
      });
    });
    Describe("with a value of false", []() {
      It("should return false when passed to eq() w/ boolean true", []() {
        AssertFalse(Equals(false, true));
      });
      It("should return true when passed to eq() w/ another boolean false", []() {
        AssertTrue(Equals(false, false));
      });
      It("should return false when compared for equality w/ a boolean true", []() {
        AssertFalse(false == true);
      });
      It("should return true when compared for equality w/ another boolean false", []() {
        AssertTrue(false == false);
      });
      It("should return EQUAL when Compare() called w/ a boolean false", []() {
        AssertEquals(Ordering::EQUAL, Compare(false, false));
      });
      It("should return LESS when Compare() called w/ a boolean true", []() {
        AssertEquals(Ordering::LESS, Compare(false, true));
      });
      It("should return 'false' when passed to Show()", []() {
        AssertEquals(String("false"), Show(false));
      });
    });
  });
}

}
