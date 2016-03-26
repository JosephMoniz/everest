#ifndef TRAITOROUS_CHECKED_SPEC_H
#define TRAITOROUS_CHECKED_SPEC_H

#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/checked.h"

namespace traitorous {

void CheckedSpecification() {
  Describe("A Checked type", []() {
    It("should have a zero value of None()", []() {
      AssertEquals(Ok<bool, int>(0), Zero<Checked<bool, int>>());
    });
    Describe("in the case of type Ok", []() {
      It("should return OK when calling GetType()", []() {
        AssertEquals(CheckedType::OK, Ok<bool, int>(42)->GetType());
      });
      It("should evalute the ok case when calling Match()", []() {
        auto result = Match(Ok<bool, int>(42),
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
        AssertTrue(result);
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, Ok<bool, int>(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, Ok<bool, int>(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(Ok<bool, int>(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(Ok<bool, int>(42)));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(Ok<bool, int>(42), Error<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(Ok<bool, int>(42), Ok<bool, int>(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(Ok<bool, int>(42) == Error<bool, int>(false));
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(Ok<bool, int>(42) == Ok<bool, int>(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(Ok<bool, int>(42) == Ok<bool, int>(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(Ok<bool, int>(42) != Error<bool, int>(false));
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(Ok<bool, int>(42) != Ok<bool, int>(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(Ok<bool, int>(42) != Ok<bool, int>(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(Ok<bool, int>(42)));
      });
      It("should return the error when called with Add() and an error", []() {
        AssertEquals(Error<bool, int>(false), Add(Ok<bool, int>(42), Error<bool, int>(false)));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(Ok<bool, int>(48), Add(Ok<bool, int>(42), Ok<bool, int>(6)));
      });
      It("should return the error when called with + and an error", []() {
        AssertEquals(Error<bool, int>(false), Ok<bool, int>(42) + Error<bool, int>(false));
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(Ok<bool, int>(48), Ok<bool, int>(42) + Ok<bool, int>(6));
      });
      It("should return GREATER when called with Compare() and an error", []() {
        AssertEquals(GREATER, Compare(Ok<bool, int>(42), Error<bool, int>(false)));
      });
      It("should return GREATER when called with Compare() and a lesser Ok()", []() {
        AssertEquals(GREATER, Compare(Ok<bool, int>(42), Ok<bool, int>(8)));
      });
      It("should return EQUAL when called with Compare() and an equal Ok()", []() {
        AssertEquals(EQUAL, Compare(Ok<bool, int>(42), Ok<bool, int>(42)));
      });
      It("should return LESS when called with Compare() and a greater Ok()", []() {
        AssertEquals(LESS, Compare(Ok<bool, int>(42), Ok<bool, int>(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(Ok<bool, int>(84), Map(Multiply(2), Ok<bool, int>(42)));
      });
      It("should return itself when called with Alt() and another Ok()", []() {
        AssertEquals(Ok<bool, int>(42), Alt(Ok<bool, int>(42), Ok<bool, int>(12)));
      });
      It("should return itself when called with Alt() and a Error()", []() {
        AssertEquals(Ok<bool, int>(42), Alt(Ok<bool, int>(42), Error<bool, int>(false)));
      });
      It("should return itself when compared with || and another Ok()", []() {
        AssertEquals(Ok<bool, int>(42), Ok<bool, int>(42) || Ok<bool, int>(12));
      });
      It("should return itself when compared with || and Error()", []() {
        AssertEquals(Ok<bool, int>(42), Ok<bool, int>(42) || Error<bool, int>(false));
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(Error<bool, int>(false), FlatMap([](auto n) { return Error<bool, int>(false); }, Ok<bool, int>(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(Ok<bool, int>(84), FlatMap([](auto n) { return Ok<bool, int>(n * 2); }, Ok<bool, int>(42)));
      });
      It("should return the next Ok(n) when called with Then()", []() {
        AssertEquals(Ok<bool, int>(42), Then(Ok<bool, int>(12), Ok<bool, int>(42)));
      });
      It("should return the error when called with Then() and an error", []() {
        AssertEquals(Error<bool, int>(false), Then(Ok<bool, int>(42), Error<bool, int>(false)));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(Ok<bool, int>(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), Ok<bool, int>(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, Ok<bool, int>(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, Ok<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, Ok<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, Ok<bool, int>(42)));
      });
      It("should return the string 'Ok(n)' when called with Show()", []() {
        AssertEquals(LocalString("Ok(42)"), Show(Ok<bool, int>(42)));
      });
    });
    Describe("in the case of type Error", []() {
      It("should return ERROR when calling GetType()", []() {
        AssertEquals(CheckedType::ERROR, Error<bool, int>(false)->GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(Error<bool, int>(false),
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, Error<bool, int>(false)));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(Error<bool, int>(false)));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(Error<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching error", []() {
        AssertTrue(Equals(Error<bool, int>(false), Error<bool, int>(false)));
      });
      It("should return false when called with Equals() and a Ok()", []() {
        AssertFalse(Equals(Error<bool, int>(false), Ok<bool, int>(42)));
      });
      It("should return true when compared with == a matching error", []() {
        AssertEquals(Error<bool, int>(false), Error<bool, int>(false));
      });
      It("should return false when compared with == and a Ok()", []() {
        AssertFalse(Error<bool, int>(false) == Ok<bool, int>(42));
      });
      It("should return false when compared with != and a matching error", []() {
        AssertFalse(Error<bool, int>(false) != Error<bool, int>(false));
      });
      It("should return true when compared with != a Ok()", []() {
        AssertTrue(Error<bool, int>(false) != Ok<bool, int>(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(Error<bool, int>(false)));
      });
      It("should return itself when called with Add() and another Error()", []() {
        AssertEquals(Error<bool, int>(false), Add(Error<bool, int>(false), Error<bool, int>(true)));
      });
      It("should return itself when called with Add() and a Ok(n)", []() {
        AssertEquals(Error<bool, int>(false), Add(Error<bool, int>(false), Ok<bool, int>(42)));
      });
      It("should return LESS when passed through Compare() with Ok()", []() {
        AssertEquals(LESS, Compare(Error<bool, int>(false), Ok<bool, int>(42)));
      });
      It("should return EQUAL when passed through Compare() with a matching Error()", []() {
        AssertEquals(EQUAL, Compare(Error<bool, int>(false), Error<bool, int>(false)));
      });
      It("should return itself when passed through Map()", []() {
        AssertEquals(Error<bool, int>(false), Map(Multiply(2), Error<bool, int>(false)));
      });
      It("should return the other error when passed through Alt() with another error", []() {
        AssertEquals(Error<bool, int>(true), Alt(Error<bool, int>(false), Error<bool, int>(true)));
      });
      It("should return the ok when passed through Alt() with Ok(n)", []() {
        AssertEquals(Ok<bool, int>(42), Alt(Error<bool, int>(false), Ok<bool, int>(42)));
      });
      It("should return the other error when passed through || with another Error()", []() {
        AssertEquals(Error<bool, int>(true), Error<bool, int>(false) || Error<bool, int>(true));
      });
      It("should return Ok(n) when passed through || with Ok(n)", []() {
        AssertEquals(Ok<bool, int>(42), Error<bool, int>(false) || Ok<bool, int>(42));
      });
      It("should return itself when called with FlatMap()", []() {
        AssertEquals(Error<bool, int>(false), FlatMap([](auto n) { return Ok<bool, int>(n * 2); }, Error<bool, int>(false)));
      });
      It("should return the first error when called with Then() and another error", []() {
        AssertEquals(Error<bool, int>(false), Then(Error<bool, int>(false), Error<bool, int>(true)));
      });
      It("should return itself when called with Then() and a Ok()", []() {
        AssertEquals(Error<bool, int>(false), Then(Error<bool, int>(false), Ok<bool, int>(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(Error<bool, int>(false)));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), Error<bool, int>(false)));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, Error<bool, int>(false)));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, Error<bool, int>(false)));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, Error<bool, int>(false)));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, Error<bool, int>(false)));
      });
      It("should return the correct string when called with Show()", []() {
        auto expected = LocalString("Error(false)");
        auto result   = Show(Error<bool, int>(false));
        AssertEquals(expected, result);
      });
    });
  });
}

}

#endif
