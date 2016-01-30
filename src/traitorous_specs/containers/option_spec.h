#ifndef TRAITOROUS_OPTION_SPEC_H
#define TRAITOROUS_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/option.h"
#include "functions/identity.h"

namespace traitorous {

void OptionSpecification() {
  describe("A Option type", []() {
    describe("in the case of type none", []() {
      it("should return false when called with Contains()", []() {
        return !Contains(42, NOne<int>());
      });
    });
    describe("in the case of type some", []() {
      it("should return true when calling Contains() with a matching item", []() {
        return Contains(42, Some(42));
      });
      it("should return false when calling Contains() with a different item", []() {
        return !Contains(12, Some(42));
      });
    });
  });
}

}

#endif
