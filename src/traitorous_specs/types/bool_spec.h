#ifndef TRAITOROUS_BOOL_SPEC_H
#define TRAITOROUS_BOOL_SPEC_H

#include <string>

#include "test/bdd.h"
#include "traits/unlawful/show.h"
#include "types/bool.h"
#include "types/int32.h"

namespace traitorous {

void BoolSpecification() {
  Describe("A type bool", []() {
    It("should have a zero value of false", []() {
      return !Zero<bool>();
    });
    Describe("with a value of true", []() {
      It("should return true when passed to eq() w/ another boolean true", []() {
        return Equals(true, true);
      });
      It("should return false when passed to eq() w/ a boolean false", []() {
        return !Equals(true, false);
      });
      It("should return true when compared for equality w/ another boolean true", []() {
        return true == true;
      });
      It("should return false when compared for equality w/ a boolean false", []() {
        return !(true == false);
      });
      It("should return EQUAL when Compare() called w/ a boolean true", []() {
        return Compare(true, true) == EQUAL;
      });
      It("should return GREATER when Compare() called w/ a boolean false", []() {
        return Compare(true, false) == GREATER;
      });
      It("should return 'true' when passed to Show()", []() {
        return LocalString("true") == Show(true);
      });
    });
    Describe("with a value of false", []() {
      It("should return false when passed to eq() w/ boolean true", []() {
        return !Equals(false, true);
      });
      It("should return true when passed to eq() w/ another boolean false", []() {
        return Equals(false, false);
      });
      It("should return false when compared for equality w/ a boolean true", []() {
        return !(false == true);
      });
      It("should return true when compared for equality w/ another boolean false", []() {
        return false == false;
      });
      It("should return EQUAL when Compare() called w/ a boolean false", []() {
        return Compare(false, false) == EQUAL;
      });
      It("should return LESS when Compare() called w/ a boolean true", []() {
        return Compare(false, true) == LESS;
      });
      It("should return 'false' when passed to Show()", []() {
        return LocalString("false") == Show(false);
      });
    });
  });
}

}

#endif
