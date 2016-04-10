#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/checked.h>

namespace everest {

void SharedCheckSpecification() {
  Describe("A SharedChecked type", []() {
    It("should have a zero value of Ok(0)", []() {
      AssertEquals(MakeSharedOk<bool, int>(0), Zero<SharedChecked<bool, int>>());
    });
    Describe("in the case of type Ok", []() {
      It("should return OK when calling GetType()", []() {
        AssertEquals(CheckedType::OK, MakeSharedOk<bool, int>(42)->GetType());
      });
      It("should evalute the ok case when calling Match()", []() {
        auto result = Match(MakeSharedOk<bool, int>(42),
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
        AssertTrue(result);
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, MakeSharedOk<bool, int>(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, MakeSharedOk<bool, int>(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(MakeSharedOk<bool, int>(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(MakeSharedOk<bool, int>(42)));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(MakeSharedOk<bool, int>(42) == MakeSharedError<bool, int>(false));
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(MakeSharedOk<bool, int>(42) == MakeSharedOk<bool, int>(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(MakeSharedOk<bool, int>(42) == MakeSharedOk<bool, int>(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(MakeSharedOk<bool, int>(42) != MakeSharedError<bool, int>(false));
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(MakeSharedOk<bool, int>(42) != MakeSharedOk<bool, int>(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(MakeSharedOk<bool, int>(42) != MakeSharedOk<bool, int>(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(MakeSharedOk<bool, int>(42)));
      });
      It("should return the error when called with Add() and an error", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Add(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false)));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(MakeSharedOk<bool, int>(48), Add(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(6)));
      });
      It("should return the error when called with + and an error", []() {
        AssertEquals(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42) + MakeSharedError<bool, int>(false));
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(MakeSharedOk<bool, int>(48), MakeSharedOk<bool, int>(42) + MakeSharedOk<bool, int>(6));
      });
      It("should return GREATER when called with Compare() and an error", []() {
        AssertEquals(Ordering::GREATER, Compare(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false)));
      });
      It("should return GREATER when called with Compare() and a lesser Ok()", []() {
        AssertEquals(Ordering::GREATER, Compare(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(8)));
      });
      It("should return EQUAL when called with Compare() and an equal Ok()", []() {
        AssertEquals(Ordering::EQUAL, Compare(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(42)));
      });
      It("should return LESS when called with Compare() and a greater Ok()", []() {
        AssertEquals(Ordering::LESS, Compare(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(MakeSharedOk<bool, int>(84), Map(Multiply(2), MakeSharedOk<bool, int>(42)));
      });
      It("should return itself when called with Alt() and another Ok()", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), Alt(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(12)));
      });
      It("should return itself when called with Alt() and a MakeSharedError()", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), Alt(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false)));
      });
      It("should return itself when compared with || and another Ok()", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(42) || MakeSharedOk<bool, int>(12));
      });
      It("should return itself when compared with || and MakeSharedError()", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), MakeSharedOk<bool, int>(42) || MakeSharedError<bool, int>(false));
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(MakeSharedError<bool, int>(false), FlatMap([](auto n) { return MakeSharedError<bool, int>(false); }, MakeSharedOk<bool, int>(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(MakeSharedOk<bool, int>(84), FlatMap([](auto n) { return MakeSharedOk<bool, int>(n * 2); }, MakeSharedOk<bool, int>(42)));
      });
      It("should return the next Ok(n) when called with Then()", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), Then(MakeSharedOk<bool, int>(12), MakeSharedOk<bool, int>(42)));
      });
      It("should return the error when called with Then() and an error", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Then(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false)));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(MakeSharedOk<bool, int>(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), MakeSharedOk<bool, int>(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, MakeSharedOk<bool, int>(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, MakeSharedOk<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, MakeSharedOk<bool, int>(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, MakeSharedOk<bool, int>(42)));
      });
      It("should return the string 'Ok(n)' when called with Show()", []() {
        AssertEquals(String("SharedOk(42)"), Show(MakeSharedOk<bool, int>(42)));
      });
    });
    Describe("in the case of type MakeSharedError", []() {
      It("should return ERROR when calling GetType()", []() {
        AssertEquals(CheckedType::ERROR, MakeSharedError<bool, int>(false)->GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(MakeSharedError<bool, int>(false),
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, MakeSharedError<bool, int>(false)));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(MakeSharedError<bool, int>(false)));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(MakeSharedError<bool, int>(false)));
      });
      It("should return true when called with Equals() and a matching error", []() {
        AssertTrue(Equals(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(false)));
      });
      It("should return false when called with Equals() and a Ok()", []() {
        AssertFalse(Equals(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42)));
      });
      It("should return true when compared with == a matching error", []() {
        AssertEquals(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(false));
      });
      It("should return false when compared with == and a Ok()", []() {
        AssertFalse(MakeSharedError<bool, int>(false) == MakeSharedOk<bool, int>(42));
      });
      It("should return false when compared with != and a matching error", []() {
        AssertFalse(MakeSharedError<bool, int>(false) != MakeSharedError<bool, int>(false));
      });
      It("should return true when compared with != a Ok()", []() {
        AssertTrue(MakeSharedError<bool, int>(false) != MakeSharedOk<bool, int>(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(MakeSharedError<bool, int>(false)));
      });
      It("should return itself when called with Add() and another MakeSharedError()", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Add(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(true)));
      });
      It("should return itself when called with Add() and a Ok(n)", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Add(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42)));
      });
      It("should return LESS when passed through Compare() with Ok()", []() {
        AssertEquals(Ordering::LESS, Compare(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42)));
      });
      It("should return EQUAL when passed through Compare() with a matching MakeSharedError()", []() {
        AssertEquals(Ordering::EQUAL, Compare(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(false)));
      });
      It("should return itself when passed through Map()", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Map(Multiply(2), MakeSharedError<bool, int>(false)));
      });
      It("should return the other error when passed through Alt() with another error", []() {
        AssertEquals(MakeSharedError<bool, int>(true), Alt(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(true)));
      });
      It("should return the ok when passed through Alt() with Ok(n)", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), Alt(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42)));
      });
      It("should return the other error when passed through || with another MakeSharedError()", []() {
        AssertEquals(MakeSharedError<bool, int>(true), MakeSharedError<bool, int>(false) || MakeSharedError<bool, int>(true));
      });
      It("should return Ok(n) when passed through || with Ok(n)", []() {
        AssertEquals(MakeSharedOk<bool, int>(42), MakeSharedError<bool, int>(false) || MakeSharedOk<bool, int>(42));
      });
      It("should return itself when called with FlatMap()", []() {
        AssertEquals(MakeSharedError<bool, int>(false), FlatMap([](auto n) { return MakeSharedOk<bool, int>(n * 2); }, MakeSharedError<bool, int>(false)));
      });
      It("should return the first error when called with Then() and another error", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Then(MakeSharedError<bool, int>(false), MakeSharedError<bool, int>(true)));
      });
      It("should return itself when called with Then() and a Ok()", []() {
        AssertEquals(MakeSharedError<bool, int>(false), Then(MakeSharedError<bool, int>(false), MakeSharedOk<bool, int>(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(MakeSharedError<bool, int>(false)));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), MakeSharedError<bool, int>(false)));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, MakeSharedError<bool, int>(false)));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, MakeSharedError<bool, int>(false)));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, MakeSharedError<bool, int>(false)));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, MakeSharedError<bool, int>(false)));
      });
      It("should return the correct string when called with Show()", []() {
        auto expected = String("SharedError(false)");
        auto result   = Show(MakeSharedError<bool, int>(false));
        AssertEquals(expected, result);
      });
    });
  });
}

}
