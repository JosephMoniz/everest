#ifndef TRAITOROUS_BOOL_SPEC_H
#define TRAITOROUS_BOOL_SPEC_H

#include <string>

#include "test/bdd.h"
#include "traits/unlawful/show.h"
#include "types/bool.h"
#include "types/int32.h"

namespace traitorous {

void bool_specification() {
  describe("A type bool", []() {
    it("should have a zero value of false", []() {
      return !Zero<bool>();
    });
    describe("with a value of true", []() {
      it("should return true when passed to eq() w/ another boolean true", []() {
        return Equals(true, true);
      });
      it("should return false when passed to eq() w/ a boolean false", []() {
        return !Equals(true, false);
      });
      it("should return true when compared for equality w/ another boolean true", []() {
        return true == true;
      });
      it("should return false when compared for equality w/ a boolean false", []() {
        return !(true == false);
      });
      it("should return EQUAL when Compare() called w/ a boolean true", []() {
        return Compare(true, true) == EQUAL;
      });
      it("should return GREATER when Compare() called w/ a boolean false", []() {
        return Compare(true, false) == GREATER;
      });
      it("should return 'true' when passed to Show()", []() {
        return std::string("true") == Show(true);
      });
    });
    describe("with a value of false", []() {
      it("should return false when passed to eq() w/ boolean true", []() {
        return !Equals(false, true);
      });
      it("should return true when passed to eq() w/ another boolean false", []() {
        return Equals(false, false);
      });
      it("should return false when compared for equality w/ a boolean true", []() {
        return !(false == true);
      });
      it("should return true when compared for equality w/ another boolean false", []() {
        return false == false;
      });
      it("should return EQUAL when Compare() called w/ a boolean false", []() {
        return Compare(false, false) == EQUAL;
      });
      it("should return LESS when Compare() called w/ a boolean true", []() {
        return Compare(false, true) == LESS;
      });
      it("should return 'false' when passed to Show()", []() {
        return std::string("false") == Show(false);
      });
    });
  });
}

}

#endif
