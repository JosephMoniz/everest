#pragma once

#include <everest/test/bdd.h>
#include <everest/functions/identity.h>
#include <everest/containers/checked.h>
#include <everest/containers/checked/all_traits.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void CheckedSpecification() {
  Describe("A Checked type", []() {
    It("should have a zero value of Ok(0)", []() {
      auto expected = Checked<bool, int>::Ok(0);
      auto result   = Checked<bool, int>::Zero();
      auto failure  = "Zero<Checked<bool, int>>() did not return Ok(0)";
      AssertEquals(failure, expected, result);
    });
    Describe("in the case of type Ok", []() {
      It("should return Ok when calling GetType()", []() {
        auto expected = CheckedType::OK;
        auto result   = Checked<bool, int>::Ok(42).GetType();
        auto failure  = "Ok(42).GetType() did not return CheckedType::OK";
        AssertEquals(failure, expected, result);
      });
      It("should evalute the Ok case when calling Match()", []() {
        auto result = Checked<bool, int>::Ok(42).Match(
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
        auto failure = "Calling Match() on Ok(42) did not execute the ok path";
        AssertTrue(failure, result);
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        auto result  = Contains(42, Checked<bool, int>::Ok(42));
        auto failure = "Contains(42, Ok(42)) did not return true";
        AssertTrue(failure, result);
      });
      It("should return false when calling Contains() with a different item", []() {
        auto result  = Contains(12, Checked<bool, int>::Ok(42));
        auto failure = "Contains(12, Ok(42)) did not return false";
        AssertFalse(failure, result);
      });
      It("should return 1 when called with Length()", []() {
        auto expected = (size_t) 1;
        auto result   = Length(Checked<bool, int>::Ok(42));
        auto failure  = "Length(Ok(42)) did not return 1";
        AssertEquals(failure, expected, result);
      });
      It("should return false when called with is_empty", []() {
        auto result  = IsEmpty(Checked<bool, int>::Ok(42));
        auto failure = "IsEmpty(Ok(42)) did not return false";
        AssertFalse(failure, result);
      });
      It("should return false when called with Equals() and a different item", []() {
        auto result  = Equals(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false));
        auto failure = "Equals(Ok(24), Error(false)) did not return false";
        AssertFalse(failure, result);
      });
      It("should return true when called with Equals() and a matching item", []() {
        auto result  = Equals(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(42));
        auto failure = "Equals(Ok(42), Ok(42)) did not return true";
        AssertTrue(failure, result);
      });
      It("should return false when compared with == and a none", []() {
        auto result  = Checked<bool, int>::Ok(42) == Checked<bool, int>::Error(false);
        auto failure = "Ok(42) == Error(false) did not evaluate to false";
        AssertFalse(failure, result);
      });
      It("should return false when compared with == and a different item", []() {
        auto result  = Checked<bool, int>::Ok(42) == Checked<bool, int>::Ok(12);
        auto failure = "Ok(42) == Ok(12) did not evaluate to false";
        AssertFalse(failure, result);
      });
      It("should return true when compared with == with a matching item", []() {
        auto result  = Checked<bool, int>::Ok(42) == Checked<bool, int>::Ok(42);
        auto failure = "Ok(42) == Ok(42) did not evaluate to true";
        AssertTrue(failure, result);
      });
      It("should return true when compared with != and a none", []() {
        auto result  = Checked<bool, int>::Ok(42) != Checked<bool, int>::Error(false);
        auto failure = "Ok(42) != Error(false) did not evaluate to true";
        AssertTrue(failure, result);
      });
      It("should return true when compared with != and a different item", []() {
        auto result  = Checked<bool, int>::Ok(42) != Checked<bool, int>::Ok(12);
        auto failure = "Ok(42) != Ok(12) did not evaluate to true";
        AssertTrue(failure, result);
      });
      It("should return false when compared with != and a matching item", []() {
        auto result  = Checked<bool, int>::Ok(42) != Checked<bool, int>::Ok(42);
        auto failure = "Ok(42) != Ok(42) did not evaluate to false";
        AssertFalse(failure, result);
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        auto expected = Hash(42);
        auto result   = Hash(Checked<bool, int>::Ok(42));
        auto failure  = "Hash(42) and Hash(Ok(42)) did not produce the same value";
        AssertEquals(failure, expected, result);
      });
      It("should return the error when called with Add() and an error", []() {
        auto expected = Checked<bool, int>::Error(false);
        auto result   = Add(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false));
        auto failure  = "Add(Ok(42), Error(false)) did not return Error(false)";
        AssertEquals(failure, expected, result);
      });
      It("should return the sum of values when called with Add() and a value", []() {
        auto expected = Checked<bool, int>::Ok(48);
        auto result   = Add(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(6));
        auto failure  = "Add(Ok(42), Ok(6)) did not return Ok(48)";
        AssertEquals(failure, expected, result);
      });
      It("should return the error when called with + and an error", []() {
        auto expected = Checked<bool, int>::Error(false);
        auto result   = Checked<bool, int>::Ok(42) + Checked<bool, int>::Error(false);
        auto failure  = "Ok(42) + Error(false) did not evaluate to Error(false)";
        AssertEquals(failure, expected, result);
      });
      It("should return the sum of values when called with + and a value", []() {
        auto expected = Checked<bool, int>::Ok(48);
        auto result   = Checked<bool, int>::Ok(42) + Checked<bool, int>::Ok(6);
        auto failure  = "Ok(42) + Ok(6) did not evaluate to Ok(48)";
        AssertEquals(failure, expected, result);
      });
      It("should return GREATER when called with Compare() and an error", []() {
        auto expected = Ordering::GREATER;
        auto result   = Compare(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false));
        auto failure  = "Compare(Ok(42), Error(false)) did not return Ordering::GREATER";
        AssertEquals(failure, expected, result);
      });
      It("should return GREATER when called with Compare() and a lesser Ok()", []() {
        auto expected = Ordering::GREATER;
        auto result   = Compare(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(8));
        auto failure  = "Compare(Ok(42), Ok(8)) did not return Ordering::GREATER";
        AssertEquals(failure, expected, result);
      });
      It("should return EQUAL when called with Compare() and an equal Ok()", []() {
        auto expected = Ordering::EQUAL;
        auto result   = Compare(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(42));
        auto failure  = "Compare(Ok(42), Ok(42)) did not return Ordering::EQUAL";
        AssertEquals(failure, expected, result);
      });
      It("should return LESS when called with Compare() and a greater Ok()", []() {
        auto expected = Ordering::LESS;
        auto result   = Compare(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(100));
        auto failure  = "Compare(Ok(42), Ok(100)) did not return Ordering::LESS";
        AssertEquals(failure, expected, result);
      });
      It("should return n * 2 when called with Map(*2)", []() {
        auto expected = Checked<bool, int>::Ok(84);
        auto result   = Map(Multiply(2), Checked<bool, int>::Ok(42));
        auto failure  = "Map(Multiply(2), Ok(42)) did not return Ok(84)";
        AssertEquals(failure, expected, result);
      });
      It("should return itself when called with Alt() and another Ok()", []() {
        auto expected = Checked<bool, int>::Ok(42);
        auto result   = Alt(Checked<bool, int>::Ok(42), Checked<bool, int>::Ok(12));
        auto failure  = "Alt(Ok(42), Ok(12)) did not return Ok(42)";
        AssertEquals(failure, expected, result);
      });
      It("should return itself when called with Alt() and a Error()", []() {
        auto expected = Checked<bool, int>::Ok(42);
        auto result   = Alt(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false));
        auto failure  = "Alt(Ok(42), Error(false)) did not return Ok(42)";
        AssertEquals(failure, expected, result);
      });
      It("should return itself when compared with || and another Ok()", []() {
        auto expected = Checked<bool, int>::Ok(42);
        auto result   = Checked<bool, int>::Ok(42) || Checked<bool, int>::Ok(12);
        auto failure  = "Ok(42) || Ok(12) did not evaluate to Ok(42)";
        AssertEquals(failure, expected, result);
      });
      It("should return itself when compared with || and Error()", []() {
        auto expected = Checked<bool, int>::Ok(42);
        auto result   = Checked<bool, int>::Ok(42) || Checked<bool, int>::Error(false);
        auto failure  = "Ok(42) || Error(false) did not evaluate to Ok(42)";
        AssertEquals(failure, expected, result);
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        auto expected = Checked<bool, int>::Error(false);
        auto mapper   = [](auto n) { return Checked<bool, int>::Error(false); };
        auto result   = FlatMap(mapper, Checked<bool, int>::Ok(42));
        auto failure  = "FlatMap((n) { return Error(false); }) did not return Error(false)";
        AssertEquals(failure, expected, result);
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        auto expected = Checked<bool, int>::Ok(84);
        auto mapper   = [](auto n) { return Checked<bool, int>::Ok(n * 2); };
        auto result   = FlatMap(mapper, Checked<bool, int>::Ok(42));
        auto failure  = "FlatMap((n) { return Ok(n * 2); }) did not return Ok(84)";
        AssertEquals(failure, expected, result);
      });
      It("should return the next Ok(n) when called with Then()", []() {
        auto expected = Checked<bool, int>::Ok(42);
        auto result   = Then(Checked<bool, int>::Ok(12), Checked<bool, int>::Ok(42));
        auto failure  = "Then(Ok(12), Ok(42)) did not return Ok(42)";
        AssertEquals(failure, expected, result);
      });
      It("should return the error when called with Then() and an error", []() {
        auto expected = Checked<bool, int>::Error(false);
        auto result   = Then(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false));
        auto failure  = "Then(Ok(42), Error(false)) did not return Error(false)";
        AssertEquals(failure, expected, result);
      });
      It("should return the inner value when called with Fold()", []() {
        auto expected = 42;
        auto result   = Fold(Checked<bool, int>::Ok(42));
        auto failure  = "Fold(Ok(42)) did not return 42";
        AssertEquals(failure, expected, result);
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        auto expected = 42;
        auto result   = FoldMap(Identity<int>(), Checked<bool, int>::Ok(42));
        auto failure  = "FoldMap(Identity(), Ok(42)) did not return 42";
        AssertEquals(failure, expected, result);
      });
      It("should return the folded value when called with FoldR()", []() {
        auto expected = 54;
        auto result   = FoldR(Add<int>(), 12, Checked<bool, int>::Ok(42));
        auto failure  = "FoldR(Add(), 12, Ok(42)) did not return 54";
        AssertEquals(failure, expected, result);
      });
      It("should return the folded value when called with FoldL()", []() {
        auto expected = 54;
        auto result   = FoldL(Add<int>(), 12, Checked<bool, int>::Ok(42));
        auto failure  = "FoldL(Add(), 12, Ok(42)) did not return 54";
        AssertEquals(failure, expected, result);
      });
      It("should return the inner value when called with GetOrElse()", []() {
        auto expected = 42;
        auto result   = GetOrElse([]() { return 12; }, Checked<bool, int>::Ok(42));
        auto failure  = "GetOrElse(() { return 12; }, Ok(42)) did not return 42";
        AssertEquals(failure, expected, result);
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        auto expected = 42;
        auto result   = GetOrDefault(12, Checked<bool, int>::Ok(42));
        auto failure  = "GetOrDefault(12, Ok(42)) did not return 42";
        AssertEquals(failure, expected, result);
      });
      It("should return the string 'Ok(n)' when called with Show()", []() {
        auto expected = String("Ok(42)");
        auto result   = Show(Checked<bool, int>::Ok(42));
        auto failure  = "Show(Ok(42)) did not return 'Ok(42)'";
        AssertEquals(failure, expected, result);
      });
    });
    Describe("in the case of type Error", []() {
      It("should return ERROR when calling GetType()", []() {
        AssertEquals(CheckedType::ERROR, Checked<bool, int>::Error(false).GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Checked<bool, int>::Error(false).Match(
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, Checked<bool, int>::Error(false)));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(Checked<bool, int>::Error(false)));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(Checked<bool, int>::Error(false)));
      });
      It("should return true when called with Equals() and a matching error", []() {
        AssertTrue(Equals(Checked<bool, int>::Error(false), Checked<bool, int>::Error(false)));
      });
      It("should return false when called with Equals() and a Ok()", []() {
        AssertFalse(Equals(Checked<bool, int>::Error(false), Checked<bool, int>::Ok(42)));
      });
      It("should return true when compared with == a matching error", []() {
        AssertEquals(Checked<bool, int>::Error(false), Checked<bool, int>::Error(false));
      });
      It("should return false when compared with == and a Ok()", []() {
        AssertFalse(Checked<bool, int>::Error(false) == Checked<bool, int>::Ok(42));
      });
      It("should return false when compared with != and a matching error", []() {
        AssertFalse(Checked<bool, int>::Error(false) != Checked<bool, int>::Error(false));
      });
      It("should return true when compared with != a Ok()", []() {
        AssertTrue(Checked<bool, int>::Error(false) != Checked<bool, int>::Ok(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(HashValue(0u), Hash(Checked<bool, int>::Error(false)));
      });
      It("should return itself when called with Add() and another Error()", []() {
        AssertEquals(Checked<bool, int>::Error(false), Add(Checked<bool, int>::Error(false), Checked<bool, int>::Error(true)));
      });
      It("should return itself when called with Add() and a Ok(n)", []() {
        AssertEquals(Checked<bool, int>::Error(false), Add(Checked<bool, int>::Error(false), Checked<bool, int>::Ok(42)));
      });
      It("should return LESS when passed through Compare() with Ok()", []() {
        AssertEquals(Ordering::LESS, Compare(Checked<bool, int>::Error(false), Checked<bool, int>::Ok(42)));
      });
      It("should return EQUAL when passed through Compare() with a matching Error()", []() {
        AssertEquals(Ordering::EQUAL, Compare(Checked<bool, int>::Error(false), Checked<bool, int>::Error(false)));
      });
      It("should return itself when passed through Map()", []() {
        AssertEquals(Checked<bool, int>::Error(false), Map(Multiply(2), Checked<bool, int>::Error(false)));
      });
      It("should return the other error when passed through Alt() with another error", []() {
        AssertEquals(Checked<bool, int>::Error(true), Alt(Checked<bool, int>::Error(false), Checked<bool, int>::Error(true)));
      });
      It("should return the Ok when passed through Alt() with Ok(n)", []() {
        AssertEquals(Checked<bool, int>::Ok(42), Alt(Checked<bool, int>::Error(false), Checked<bool, int>::Ok(42)));
      });
      It("should return the other error when passed through || with another Error()", []() {
        AssertEquals(Checked<bool, int>::Error(true), Checked<bool, int>::Error(false) || Checked<bool, int>::Error(true));
      });
      It("should return Ok(n) when passed through || with Ok(n)", []() {
        AssertEquals(Checked<bool, int>::Ok(42), Checked<bool, int>::Error(false) || Checked<bool, int>::Ok(42));
      });
      It("should return itself when called with FlatMap()", []() {
        AssertEquals(Checked<bool, int>::Error(false), FlatMap([](auto n) { return Checked<bool, int>::Ok(n * 2); }, Checked<bool, int>::Error(false)));
      });
      It("should return the first error when called with Then() and another error", []() {
        AssertEquals(Checked<bool, int>::Error(false), Then(Checked<bool, int>::Error(false), Checked<bool, int>::Error(true)));
      });
      It("should return itself when called with Then() and a Ok()", []() {
        AssertEquals(Checked<bool, int>::Error(false), Then(Checked<bool, int>::Error(false), Checked<bool, int>::Ok(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(Checked<bool, int>::Error(false)));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), Checked<bool, int>::Error(false)));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, Checked<bool, int>::Error(false)));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, Checked<bool, int>::Error(false)));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, Checked<bool, int>::Error(false)));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, Checked<bool, int>::Error(false)));
      });
      It("should return the correct string when called with Show()", []() {
        auto expected = String("Error(false)");
        auto result   = Show(Checked<bool, int>::Error(false));
        AssertEquals(expected, result);
      });
    });
  });
}

}
