#ifndef TRAITOROUS_CHECKED_SPEC_H
#define TRAITOROUS_CHECKED_SPEC_H

#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/checked.h"

namespace traitorous {

void CheckedSpecification() {
  Describe("A Checked type", []() {
    It("should have a zero value of None()", []() {
      return Zero<Checked<bool, int>>() == Ok<bool, int>(0);
    });
    Describe("in the case of type Ok", []() {
      It("should return OK when calling GetType()", []() {
        return Ok<bool, int>(42)->GetType() == CheckedType::OK;
      });
      It("should evalute the ok case when calling Match()", []() {
        return Match(Ok<bool, int>(42),
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        return Contains(42, Ok<bool, int>(42));
      });
      It("should return false when calling Contains() with a different item", []() {
        return !Contains(12, Ok<bool, int>(42));
      });
      It("should return 1 when called with Length()", []() {
        return Length(Ok<bool, int>(42)) == 1;
      });
      It("should return false when called with is_empty", []() {
        return !IsEmpty(Ok<bool, int>(42));
      });
      It("should return false when called with Equals() and a different item", []() {
        return !Equals(Ok<bool, int>(42), Error<bool, int>(false));
      });
      It("should return true when called with Equals() and a matching item", []() {
        return Equals(Ok<bool, int>(42), Ok<bool, int>(42));
      });
      It("should return false when compared with == and a none", []() {
        return !(Ok<bool, int>(42) == Error<bool, int>(false));
      });
      It("should return false when compared with == and a different item", []() {
        return !(Ok<bool, int>(42) == Ok<bool, int>(12));
      });
      It("should return true when compared with == with a matching item", []() {
        return Ok<bool, int>(42) == Ok<bool, int>(42);
      });
      It("should return true when compared with != and a none", []() {
        return Ok<bool, int>(42) != Error<bool, int>(false);
      });
      It("should return true when compared with != and a different item", []() {
        return Ok<bool, int>(42) != Ok<bool, int>(12);
      });
      It("should return false when compared with != and a matching item", []() {
        return !(Ok<bool, int>(42) != Ok<bool, int>(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        return Hash(Ok<bool, int>(42)) == Hash(42);
      });
      It("should return the error when called with Add() and an error", []() {
        return Add(Ok<bool, int>(42), Error<bool, int>(false)) == Error<bool, int>(false);
      });
      It("should return the sum of values when called with Add() and a value", []() {
        return Add(Ok<bool, int>(42), Ok<bool, int>(6)) == Ok<bool, int>(48);
      });
      It("should return the error when called with + and an error", []() {
        return (Ok<bool, int>(42) + Error<bool, int>(false)) == Error<bool, int>(false);
      });
      It("should return the sum of values when called with + and a value", []() {
        return (Ok<bool, int>(42) + Ok<bool, int>(6)) == Ok<bool, int>(48);
      });
      It("should return GREATER when called with Compare() and an error", []() {
        return Compare(Ok<bool, int>(42), Error<bool, int>(false)) == GREATER;
      });
      It("should return GREATER when called with Compare() and a lesser Ok()", []() {
        return Compare(Ok<bool, int>(42), Ok<bool, int>(8)) == GREATER;
      });
      It("should return EQUAL when called with Compare() and an equal Ok()", []() {
        return Compare(Ok<bool, int>(42), Ok<bool, int>(42)) == EQUAL;
      });
      It("should return LESS when called with Compare() and a greater Ok()", []() {
        return Compare(Ok<bool, int>(42), Ok<bool, int>(100)) == LESS;
      });
      It("should return n * 2 when called with Map(*2)", []() {
        return Map(Multiply(2), Ok<bool, int>(42)) == Ok<bool, int>(84);
      });
      It("should return itself when called with Alt() and another Ok()", []() {
        return Alt(Ok<bool, int>(42), Ok<bool, int>(12)) == Ok<bool, int>(42);
      });
      It("should return itself when called with Alt() and a Error()", []() {
        return Alt(Ok<bool, int>(42), Error<bool, int>(false)) == Ok<bool, int>(42);
      });
      It("should return itself when compared with || and another Ok()", []() {
        return (Ok<bool, int>(42) || Ok<bool, int>(12)) == Ok<bool, int>(42);
      });
      It("should return itself when compared with || and Error()", []() {
        return (Ok<bool, int>(42) || Error<bool, int>(false)) == Ok<bool, int>(42);
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        return FlatMap([](auto n) { return Error<bool, int>(false); }, Ok<bool, int>(42)) == Error<bool, int>(false);
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        return FlatMap([](auto n) { return Ok<bool, int>(n * 2); }, Ok<bool, int>(42)) == Ok<bool, int>(84);
      });
      It("should return the next Ok(n) when called with Then()", []() {
        return Then(Ok<bool, int>(12), Ok<bool, int>(42)) == Ok<bool, int>(42);
      });
      It("should return the error when called with Then() and an error", []() {
        return Then(Ok<bool, int>(42), Error<bool, int>(false)) == Error<bool, int>(false);
      });
      It("should return the inner value when called with Fold()", []() {
        return Fold(Ok<bool, int>(42)) == 42;
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        return FoldMap(Identity<int>(), Ok<bool, int>(42)) == 42;
      });
      It("should return the folded value when called with FoldR()", []() {
        return FoldR(Add<int>(), 12, Ok<bool, int>(42)) == 54;
      });
      It("should return the folded value when called with FoldL()", []() {
        return FoldL(Add<int>(), 12, Ok<bool, int>(42)) == 54;
      });
      It("should return the inner value when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, Ok<bool, int>(42)) == 42;
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        return GetOrDefault(12, Ok<bool, int>(42)) == 42;
      });
      It("should return the string 'Ok(n)' when called with Show()", []() {
        return Show(Ok<bool, int>(42)) == LocalString("Ok(42)");
      });
    });
    Describe("in the case of type Error", []() {
      It("should return ERROR when calling GetType()", []() {
        return Error<bool, int>(false)->GetType() == CheckedType::ERROR;
      });
      It("should evalute the none case when calling Match()", []() {
        return Match(Error<bool, int>(false),
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
      });
      It("should return false when called with Contains()", []() {
        return !Contains(42, Error<bool, int>(false));
      });
      It("should return 0 when called with Length()", []() {
        return Length(Error<bool, int>(false)) == 0;
      });
      It("should return true when called with IsEmpty()", []() {
        return IsEmpty(Error<bool, int>(false));
      });
      It("should return true when called with Equals() and a matching error", []() {
        return Equals(Error<bool, int>(false), Error<bool, int>(false));
      });
      It("should return false when called with Equals() and a Ok()", []() {
        return !Equals(Error<bool, int>(false), Ok<bool, int>(42));
      });
      It("should return true when compared with == a matching error", []() {
        return Error<bool, int>(false) == Error<bool, int>(false);
      });
      It("should return false when compared with == and a Ok()", []() {
        return !(Error<bool, int>(false) == Ok<bool, int>(42));
      });
      It("should return false when compared with != and a matching error", []() {
        return !(Error<bool, int>(false) != Error<bool, int>(false));
      });
      It("should return true when compared with != a Ok()", []() {
        return Error<bool, int>(false) != Ok<bool, int>(42);
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        return Hash(Error<bool, int>(false)) == 0;
      });
      It("should return itself when called with Add() and another Error()", []() {
        return Add(Error<bool, int>(false), Error<bool, int>(true)) == Error<bool, int>(false);
      });
      It("should return itself when called with Add() and a Ok(n)", []() {
        return Add(Error<bool, int>(false), Ok<bool, int>(42)) == Error<bool, int>(false);
      });
      It("should return LESS when passed through Compare() with Ok()", []() {
        return Compare(Error<bool, int>(false), Ok<bool, int>(42)) == LESS;
      });
      It("should return EQUAL when passed through Compare() with a matching Error()", []() {
        return Compare(Error<bool, int>(false), Error<bool, int>(false)) == EQUAL;
      });
      It("should return itself when passed through Map()", []() {
        return Map(Multiply(2), Error<bool, int>(false)) == Error<bool, int>(false);
      });
      It("should return the other error when passed through Alt() with another error", []() {
        return Alt(Error<bool, int>(false), Error<bool, int>(true)) == Error<bool, int>(true);
      });
      It("should return the ok when passed through Alt() with Ok(n)", []() {
        return Alt(Error<bool, int>(false), Ok<bool, int>(42)) == Ok<bool, int>(42);
      });
      It("should return the other error when passed through || with another Error()", []() {
        return (Error<bool, int>(false) || Error<bool, int>(true)) == Error<bool, int>(true);
      });
      It("should return Ok(n) when passed through || with Ok(n)", []() {
        return (Error<bool, int>(false) || Ok<bool, int>(42)) == Ok<bool, int>(42);
      });
      It("should return itself when called with FlatMap()", []() {
        return FlatMap([](auto n) { return Ok<bool, int>(n * 2); }, Error<bool, int>(false)) == Error<bool, int>(false);
      });
      It("should return the first error when called with Then() and another error", []() {
        return Then(Error<bool, int>(false), Error<bool, int>(true)) == Error<bool, int>(false);
      });
      It("should return itself when called with Then() and a Ok()", []() {
        return Then(Error<bool, int>(false), Ok<bool, int>(42)) == Error<bool, int>(false);
      });
      It("should return zero when called with Fold()", []() {
        return Fold(Error<bool, int>(false)) == 0;
      });
      It("should return zero when called with foldMap()", []() {
        return FoldMap(Identity<int>(), Error<bool, int>(false)) == 0;
      });
      It("should return init when called with FoldR()", []() {
        return FoldR(Add<int>(), 0, Error<bool, int>(false)) == 0;
      });
      It("should return init when called with FoldL()", []() {
        return FoldL(Add<int>(), 0, Error<bool, int>(false)) == 0;
      });
      It("should return the alternative when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, Error<bool, int>(false)) == 12;
      });
      It("should return the default when called with GetOrDefault()", []() {
        return GetOrDefault(42, Error<bool, int>(false)) == 42;
      });
      It("should return the correct string when called with Show()", []() {
        auto expected = LocalString("Error(false)");
        auto result   = Show(Error<bool, int>(false));
        return result == expected;
      });
    });
  });
}

}

#endif
