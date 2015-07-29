#ifndef TRAITOROUS_BOOL_SPEC_H
#define TRAITOROUS_BOOL_SPEC_H

#include <string>

#include "test/bdd.h"
#include "traits/show.h"
#include "types/bool.h"
#include "types/int32.h"

namespace traitorous {

void bool_specification() {
  describe("A type bool", []() {
    it("should have a zero value of false", []() {
      return !zero<bool>();
    });
    describe("with a value of true", []() {
      it("should return true when passed to eq() w/ another boolean true", []() {
        return equals(true, true);
      });
      it("should return false when passed to eq() w/ a boolean false", []() {
        return !equals(true, false);
      });
      it("should return true when compared for equality w/ another boolean true", []() {
        return true == true;
      });
      it("should return false when compared for equality w/ a boolean false", []() {
        return !(true == false);
      });
      it("should return EQUAL when cmp() called w/ a boolean true", []() {
        return cmp(true, true) == EQUAL;
      });
      it("should return GREATER when cmp() called w/ a boolean false", []() {
        return cmp(true, false) == GREATER;
      });
      it("should return 'true' when passed to show()", []() {
        return std::string("true") == show(true);
      });
    });
    describe("with a value of false", []() {
      it("should return false when passed to eq() w/ boolean true", []() {
        return !equals(false, true);
      });
      it("should return true when passed to eq() w/ another boolean false", []() {
        return equals(false, false);
      });
      it("should return false when compared for equality w/ a boolean true", []() {
        return !(false == true);
      });
      it("should return true when compared for equality w/ another boolean false", []() {
        return false == false;
      });
      it("should return EQUAL when cmp() called w/ a boolean false", []() {
        return cmp(false, false) == EQUAL;
      });
      it("should return LESS when cmp() called w/ a boolean true", []() {
        return cmp(false, true) == LESS;
      });
      it("should return 'false' when passed to show()", []() {
        return std::string("false") == show(false);
      });
    });
  });
}

}

#endif
