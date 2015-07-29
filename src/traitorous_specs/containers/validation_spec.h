#ifndef TRAITOROUS_VALIDATION_SPEC_H
#define TRAITOROUS_VALIDATION_SPEC_H

#include "test/bdd.h"

#include "containers/validation.h"

namespace traitorous {

void validation_specification() {
  describe("A validation type", []() {
    describe("with a failure value", []() {
      it("should evalute the failure case when called with match()", []() {
        return match(failure<int, int>(42),
          [](auto f) { return f == 42; },
          [](auto s) { return false; }
        );
      });
      it("should return false when called with contains()", []() {
        return !contains(42, failure<int, int>(42));
      });
      it("should return 0 when called with length()", []() {
        return length(failure<int, int>(42)) == 0;
      });
      it("should return true when called with is_empty()", []() {
        return is_empty(failure<int, int>(42));
      });
      it("should return false when passed through equals() with a non matching failure", []() {
        return !equals(failure<int, int>(42), failure<int, int>(12));
      });
      it("should return false when passed through equals() with a success", []() {
        return !equals(failure<int, int>(42), success<int, int>(12));
      });
      it("should return true when passed through equals() with a matching failure", []() {
        return equals(failure<int, int>(42), failure<int, int>(42));
      });
      it("should return false when passed through == with a non matching failure", []() {
        return !(failure<int, int>(42) == failure<int, int>(12));
      });
      it("should return false when passed through == with a success", []() {
        return !(failure<int, int>(42) == success<int, int>(12));
      });
      it("should return true when passed through == with a matching failure", []() {
        return failure<int, int>(42) == failure<int, int>(42);
      });
      it("should return true when passed through != with a non matching failure", []() {
        return failure<int, int>(42) != failure<int, int>(12);
      });
      it("should return true when passed through != with a success", []() {
        return failure<int, int>(42) != success<int, int>(12);
      });
      it("should return false when passed through != with a matching failure", []() {
        return !(failure<int, int>(42) != failure<int, int>(42));
      });
      it("should return itself when called with add() and a success value", []() {
        return add(failure<int, int>(42), success<int, int>(12)) == failure<int, int>(42);
      });
      it("should return the sum of inner values when called with add() and a failure", []() {
        return add(failure<int, int>(42), failure<int, int>(12)) == failure<int, int>(54);
      });
      it("should return itself when called with + and a success value", []() {
        return (failure<int, int>(42) + success<int, int>(12)) == failure<int, int>(42);
      });
      it("should return the sum of inner values when called with + and a failure", []() {
        return (failure<int, int>(42) + failure<int, int>(12)) == failure<int, int>(54);
      });
      it("should return itself when called with filter()", []() {
        return filter(equals(42), failure<int, int>(42)) == failure<int, int>(42);
      });
      it("should return LESS when called with cmp() and a success", []() {
        return cmp(failure<int, int>(42), success<int, int>(42)) == LESS;
      });
      it("should return LESS when called with cmp() and a greater failure", []() {
        return cmp(failure<int, int>(42), failure<int, int>(54)) == LESS;
      });
      it("should return EQUAL when called with cmp() and an equal failure", []() {
        return cmp(failure<int, int>(42), failure<int, int>(42)) == EQUAL;
      });
      it("should return GREATER when called with cmp() and a lesser failure", []() {
        return cmp(failure<int, int>(42), failure<int, int>(12)) == GREATER;
      });
      it("should return itself when called with map()", []() {
        return map(multiply(2), failure<int, int>(42)) == failure<int, int>(42);
      });
      it("should return itself when called with ap() and a success functor"/*, []() {
        return ap(success<int>(multiply(2)), failure<int, int>(42)) == failure<int, int>(42);
      }*/);
      it("should return the other value when called with alt()", []() {
        return alt(failure<int, int>(42), failure<int, int>(12)) == failure<int, int>(12);
      });
      it("should return the other value when passed through ||", []() {
        return (failure<int, int>(42) || failure<int, int>(12)) == failure<int, int>(12);
      });
      it("should return itself when called with flat_map()", []() {
        return flat_map([](auto n) { return success<int, int>(n * 2); }, failure<int, int>(42)) == failure<int, int>(42);
      });
      it("should return the other value when passed through mplus()", []() {
        return mplus(failure<int, int>(42), failure<int, int>(12)) == failure<int, int>(12);
      });
      it("should return the success zero value when called with fold()", []() {
        return fold(failure<int, int>(42)) == 0;
      });
      it("should return the success value when called with fold_map()", []() {
        return fold_map(add(2), failure<int, int>(42)) == 0;
      });
      it("should return the init value when called with foldl()", []() {
        return foldl(add<int>(), 0, failure<int, int>(42)) == 0;
      });
      it("should return the initi value when called with foldr()", []() {
        return foldr(add<int>(), 0, failure<int, int>(42)) == 0;
      });
      it("should return the alternative when called with get_or_else()", []() {
        return get_or_else([]() { return 42; }, failure<int, int>(12)) == 42;
      });
      it("should return the default when called with get_or_default()", []() {
        return get_or_default(42, failure<int, int>(12)) == 42;
      });
      it("should return the failure as a string when called with show()", []() {
        return show(failure<int, int>(42))  == "failure(42)";
      });
    });
    describe("with a success value", []() {
      it("should evalute the success case when called with match()", []() {
        return match(success<int, int>(42),
          [](auto f) { return false; },
          [](auto s) { return s == 42; }
        );
      });
      it("should return true when called with contains() and a matching item", []() {
        return contains(42, success<int, int>(42));
      });
      it("should retur false when called with contains() and a non matching item", []() {
        return !contains(12, success<int, int>(42));
      });
      it("should return 1 when called with length()", []() {
        return length(success<int, int>(42)) == 1;
      });
      it("should return false when called with is_empty()", []() {
        return !is_empty(success<int, int>(42));
      });
      it("should return false when called with equals() with a non matching success", []() {
        return !equals(success<int, int>(42), success<int, int>(12));
      });
      it("should return false when called with equals() and a failure", []() {
        return !equals(success<int, int>(42), failure<int, int>(12));
      });
      it("should return true when called with equals() and a matching success", []() {
        return equals(success<int, int>(42), success<int, int>(42));
      });
      it("should return false when called with == with a non matching success", []() {
        return !(success<int, int>(42) == success<int, int>(12));
      });
      it("should return false when called with == and a failure", []() {
        return !(success<int, int>(42) == failure<int, int>(12));
      });
      it("should return true when called with == and a matching success", []() {
        return success<int, int>(42) == success<int, int>(42);
      });
      it("should return true when called with != and a non matching success", []() {
        return success<int, int>(42) != success<int, int>(12);
      });
      it("should return true when called with != and a failure", []() {
        return success<int, int>(42) != failure<int, int>(42);
      });
      it("should return false when called with != and a matching success", []() {
        return !(success<int, int>(42) != success<int, int>(42));
      });
      it("should return the sum of inner values when called with add() and a success", []() {
        return add(success<int, int>(42), success<int, int>(12)) == success<int, int>(54);
      });
      it("should return the failure when called with add() and a failure", []() {
        return add(success<int, int>(42), failure<int, int>(12)) == failure<int, int>(12);
      });
      it("should return the sum of inner values when called with + and a success", []() {
        return (success<int, int>(42) + success<int, int>(12)) == success<int, int>(54);
      });
      it("should return the failure when called with + and a failure", []() {
        return (success<int, int>(42) + failure<int, int>(12)) == failure<int, int>(12);
      });
      it("should return a success with zero when called with filter() and a non matching predicate", []() {
        return filter(equals(12), success<int, int>(42)) == success<int, int>(0);
      });
      it("should return itself when called with filter() and a matching predicate", []() {
        return filter(equals(42), success<int, int>(42)) == success<int, int>(42);
      });
      it("should return GREATER when called with cmp() and a failure", []() {
        return cmp(success<int, int>(43), failure<int, int>(54)) == GREATER;
      });
      it("should return LESS when called with cmp() and a greater success", []() {
        return cmp(success<int, int>(43), success<int, int>(54)) == LESS;
      });
      it("should return EQUAL when called with cmp() and an equal success", []() {
        return cmp(success<int, int>(43), success<int, int>(43)) == EQUAL;
      });
      it("should return GREATER when called with cmp() and a lesser success", []() {
        return cmp(success<int, int>(43), success<int, int>(12)) == GREATER;
      });
      it("should return n*2 when called with map() and *2", []() {
        return map(multiply(2), success<int, int>(12)) == success<int, int>(24);
      });
      it("should return itself when called through alt()", []() {
        return alt(success<int, int>(42), success<int, int>(12)) == success<int, int>(42);
      });
      it("should return itself when called through ||", []() {
        return (success<int, int>(42) || success<int, int>(12)) == success<int, int>(42);
      });
      it("should apply n*2 when called with flat_map() and n*2", []() {
        return flat_map([](auto n) { return success<int, int>(n * 2); }, success<int, int>(42)) == success<int, int>(84);
      });
      it("should return failure when called with flat_map() -> failure", []() {
        return flat_map([](auto n) { return failure<int, int>(n * 2); }, success<int, int>(42)) == failure<int, int>(84);
      });
      it("should return itself when passed through mplus()", []() {
        return mplus(success<int, int>(42), failure<int, int>(12)) == success<int, int>(42);
      });
      it("should return the inner value when called with foldl()", []() {
        return foldl(add<int>(), 0, success<int, int>(42)) == 42;
      });
      it("should return the inner value when called with foldr()", []() {
        return foldr(add<int>(), 0, success<int, int>(42)) == 42;
      });
      it("should return the success as a string when called with show()", []() {
        return show(success<int, int>(42))  == "success(42)";
      });
    });
  });
}

}

#endif
