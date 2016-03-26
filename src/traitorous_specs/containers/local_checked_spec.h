#ifndef TRAITOROUS_LOCAL_CHECKED_SPEC_H
#define TRAITOROUS_LOCAL_CHECKED_SPEC_H

#include <traits/unlawful/containable.h>
#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/checked.h"

namespace traitorous {

void LocalCheckedSpecification() {
  Describe("A LocalChecked type", []() {
    It("should have a zero value of LocalOk(0)", []() {
      AssertEquals(LocalOk<bool, int>(0), Zero<LocalChecked<bool, int>>());
    });
    Describe("in the case of type LocalOk", []() {
      It("should return LocalOk when calling GetType()", []() {
        AssertEquals(CheckedType::OK, LocalOk<bool, int>(42).GetType());
      });
      It("should evalute the LocalOk case when calling Match()", []() {
        auto result = Match(LocalOk<bool, int>(42),
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
        AssertTrue(result);
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, LocalOk<bool, int>(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, LocalOk<bool, int>(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(LocalOk<bool, int>(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(LocalOk<bool, int>(42)));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(LocalOk<bool, int>(42), LocalError<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(LocalOk<bool, int>(42), LocalOk<bool, int>(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(LocalOk<bool, int>(42) == LocalError<bool, int>(false));
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(LocalOk<bool, int>(42) == LocalOk<bool, int>(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(LocalOk<bool, int>(42) == LocalOk<bool, int>(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(LocalOk<bool, int>(42) != LocalError<bool, int>(false));
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(LocalOk<bool, int>(42) != LocalOk<bool, int>(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(LocalOk<bool, int>(42) != LocalOk<bool, int>(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(LocalOk<bool, int>(42)));
      });
      It("should return the error when called with Add() and an error", []() {
        AssertEquals(LocalError<bool, int>(false), Add(LocalOk<bool, int>(42), LocalError<bool, int>(false)));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(LocalOk<bool, int>(48), Add(LocalOk<bool, int>(42), LocalOk<bool, int>(6)));
      });
      It("should return the error when called with + and an error", []() {
        AssertEquals(LocalError<bool, int>(false), LocalOk<bool, int>(42) + LocalError<bool, int>(false));
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(LocalOk<bool, int>(48), LocalOk<bool, int>(42) + LocalOk<bool, int>(6));
      });
      It("should return GREATER when called with Compare() and an error", []() {
        AssertEquals(GREATER, Compare(LocalOk<bool, int>(42), LocalError<bool, int>(false)));
      });
      It("should return GREATER when called with Compare() and a lesser LocalOk()", []() {
        AssertEquals(GREATER, Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(8)));
      });
      It("should return EQUAL when called with Compare() and an equal LocalOk()", []() {
        AssertEquals(EQUAL, Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(42)));
      });
      It("should return LESS when called with Compare() and a greater LocalOk()", []() {
        AssertEquals(LESS, Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(LocalOk<bool, int>(84), Map(Multiply(2), LocalOk<bool, int>(42)));
      });
      It("should return itself when called with Alt() and another LocalOk()", []() {
        AssertEquals(LocalOk<bool, int>(42), Alt(LocalOk<bool, int>(42), LocalOk<bool, int>(12)));
      });
      It("should return itself when called with Alt() and a LocalError()", []() {
        AssertEquals(LocalOk<bool, int>(42), Alt(LocalOk<bool, int>(42), LocalError<bool, int>(false)));
      });
      It("should return itself when compared with || and another LocalOk()", []() {
        AssertEquals(LocalOk<bool, int>(42), LocalOk<bool, int>(42) || LocalOk<bool, int>(12));
      });
      It("should return itself when compared with || and LocalError()", []() {
        AssertEquals(LocalOk<bool, int>(42), LocalOk<bool, int>(42) || LocalError<bool, int>(false));
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(LocalError<bool, int>(false), FlatMap([](auto n) { return LocalError<bool, int>(false); }, LocalOk<bool, int>(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(LocalOk<bool, int>(84), FlatMap([](auto n) { return LocalOk<bool, int>(n * 2); }, LocalOk<bool, int>(42)));
      });
      It("should return the next LocalOk(n) when called with Then()", []() {
        AssertEquals(LocalOk<bool, int>(42), Then(LocalOk<bool, int>(12), LocalOk<bool, int>(42)));
      });
      It("should return the error when called with Then() and an error", []() {
        AssertEquals(LocalError<bool, int>(false), Then(LocalOk<bool, int>(42), LocalError<bool, int>(false)));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(LocalOk<bool, int>(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), LocalOk<bool, int>(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, LocalOk<bool, int>(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, LocalOk<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, LocalOk<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, LocalOk<bool, int>(42)));
      });
      It("should return the string 'LocalOk(n)' when called with Show()", []() {
        AssertEquals(LocalString("LocalOk(42)"), Show(LocalOk<bool, int>(42)));
      });
    });
    Describe("in the case of type LocalError", []() {
      It("should return ERROR when calling GetType()", []() {
        AssertEquals(CheckedType::ERROR, LocalError<bool, int>(false).GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(LocalError<bool, int>(false),
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, LocalError<bool, int>(false)));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(LocalError<bool, int>(false)));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(LocalError<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching error", []() {
        AssertTrue(Equals(LocalError<bool, int>(false), LocalError<bool, int>(false)));
      });
      It("should return false when called with Equals() and a LocalOk()", []() {
        AssertFalse(Equals(LocalError<bool, int>(false), LocalOk<bool, int>(42)));
      });
      It("should return true when compared with == a matching error", []() {
        AssertEquals(LocalError<bool, int>(false), LocalError<bool, int>(false));
      });
      It("should return false when compared with == and a LocalOk()", []() {
        AssertFalse(LocalError<bool, int>(false) == LocalOk<bool, int>(42));
      });
      It("should return false when compared with != and a matching error", []() {
        AssertFalse(LocalError<bool, int>(false) != LocalError<bool, int>(false));
      });
      It("should return true when compared with != a LocalOk()", []() {
        AssertTrue(LocalError<bool, int>(false) != LocalOk<bool, int>(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(LocalError<bool, int>(false)));
      });
      It("should return itself when called with Add() and another LocalError()", []() {
        AssertEquals(LocalError<bool, int>(false), Add(LocalError<bool, int>(false), LocalError<bool, int>(true)));
      });
      It("should return itself when called with Add() and a LocalOk(n)", []() {
        AssertEquals(LocalError<bool, int>(false), Add(LocalError<bool, int>(false), LocalOk<bool, int>(42)));
      });
      It("should return LESS when passed through Compare() with LocalOk()", []() {
        AssertEquals(LESS, Compare(LocalError<bool, int>(false), LocalOk<bool, int>(42)));
      });
      It("should return EQUAL when passed through Compare() with a matching LocalError()", []() {
        AssertEquals(EQUAL, Compare(LocalError<bool, int>(false), LocalError<bool, int>(false)));
      });
      It("should return itself when passed through Map()", []() {
        AssertEquals(LocalError<bool, int>(false), Map(Multiply(2), LocalError<bool, int>(false)));
      });
      It("should return the other error when passed through Alt() with another error", []() {
        AssertEquals(LocalError<bool, int>(true), Alt(LocalError<bool, int>(false), LocalError<bool, int>(true)));
      });
      It("should return the LocalOk when passed through Alt() with LocalOk(n)", []() {
        AssertEquals(LocalOk<bool, int>(42), Alt(LocalError<bool, int>(false), LocalOk<bool, int>(42)));
      });
      It("should return the other error when passed through || with another LocalError()", []() {
        AssertEquals(LocalError<bool, int>(true), LocalError<bool, int>(false) || LocalError<bool, int>(true));
      });
      It("should return LocalOk(n) when passed through || with LocalOk(n)", []() {
        AssertEquals(LocalOk<bool, int>(42), LocalError<bool, int>(false) || LocalOk<bool, int>(42));
      });
      It("should return itself when called with FlatMap()", []() {
        AssertEquals(LocalError<bool, int>(false), FlatMap([](auto n) { return LocalOk<bool, int>(n * 2); }, LocalError<bool, int>(false)));
      });
      It("should return the first error when called with Then() and another error", []() {
        AssertEquals(LocalError<bool, int>(false), Then(LocalError<bool, int>(false), LocalError<bool, int>(true)));
      });
      It("should return itself when called with Then() and a LocalOk()", []() {
        AssertEquals(LocalError<bool, int>(false), Then(LocalError<bool, int>(false), LocalOk<bool, int>(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(LocalError<bool, int>(false)));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), LocalError<bool, int>(false)));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, LocalError<bool, int>(false)));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, LocalError<bool, int>(false)));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, LocalError<bool, int>(false)));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, LocalError<bool, int>(false)));
      });
      It("should return the correct string when called with Show()", []() {
        auto expected = LocalString("LocalError(false)");
        auto result   = Show(LocalError<bool, int>(false));
        AssertEquals(expected, result);
      });
    });
  });
}

}

#endif
