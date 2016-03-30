#pragma once

#include <test/bdd.h>
#include <functions/identity.h>
#include <containers/option.h>

namespace traitorous {

void OptionSpecification() {
  Describe("A Option type", []() {
    It("should have a zero value of None()", []() {
      AssertEquals(None<int>(), Zero<Option<int>> ());
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        AssertEquals(OptionType::NONE, None<int>().GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(None<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, None<int>()));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(None<int>()));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(None<int>()));
      });
      It("should return true when called with Equals() and another none", []() {
        AssertTrue(Equals(None<int>(), None<int>()));
      });
      It("should return false when called with Equals() and a Some()", []() {
        AssertFalse(Equals(None<int>(), Some(42)));
      });
      It("should return true when compared with == and another none", []() {
        AssertTrue(None<int>() == None<int>());
      });
      It("should return false when compared with == and a Some()", []() {
        AssertFalse(None<int>() == Some(42));
      });
      It("should return false when compared with != and another none", []() {
        AssertFalse(None<int>() != None<int>());
      });
      It("should return true when compared with != a Some()", []() {
        AssertTrue(None<int>() != Some(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(None<int>()));
      });
      It("should return none when called with Add() and another None()", []() {
        AssertEquals(None<int>(), Add(None<int>(), None<int>()));
      });
      It("should return Some(n) when called with Add() and a Some(n)", []() {
        AssertEquals(Some(42), Add(None<int>(), Some(42)));
      });
      It("should return None() when called with Filter()", []() {
        AssertEquals(None<int>(), Filter(Equals(42), None<int>()));
      });
      It("should return LESS when passed through Compare() with Some()", []() {
        AssertEquals(Ordering::LESS, Compare(None<int>(), Some(42)));
      });
      It("should return EQUAL when passed through Compare() with another None()", []() {
        AssertEquals(Ordering::EQUAL, Compare(None<int>(), None<int>()));
      });
      It("should return None() when passed through Map()", []() {
        AssertEquals(None<int>(), Map(Multiply(2), None<int>()));
      });
      It("should return LocalNone() when passed through Alt() with another None()", []() {
        AssertEquals(None<int>(), Alt(None<int>(), None<int>()));
      });
      It("should return Some(n) when passed through Alt() with Some(n)", []() {
        AssertEquals(Some(42), Alt(None<int>(), Some(42)));
      });
      It("should return LocalNone() when passed through || with another None()", []() {
        AssertEquals(None<int>(), None<int>() || None<int>());
      });
      It("should return Some(n) when passed through || with Some(n)", []() {
        AssertEquals(Some(42), None<int>() || Some(42));
      });
      It("should return None() when called with FlatMap()", []() {
        AssertEquals(None<int>(), FlatMap([](auto n) { return Some(n * 2); }, None<int>()));
      });
      It("should return None() when called with Then() and another none", []() {
        AssertEquals(None<int>(), Then(None<int>(), None<int>()));
      });
      It("should return None() when called with Then() and a Some()", []() {
        AssertEquals(None<int>(), Then(None<int>(), Some(42)));
      });
      It("should return None() when called with MPlus() and another LocalNone()", []() {
        AssertEquals(None<int>(), MPlus(None<int>(), None<int>()));
      });
      It("should return Some(n) when called with MPlus() and another Some(n)", []() {
        AssertEquals(Some(42), MPlus(None<int>(), Some(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(None<int>()));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), None<int>()));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, None<int>()));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, None<int>()));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, None<int>()));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, None<int>()));
      });
      It("should return the string 'none' when called with Show()", []() {
        AssertEquals(String("None"), Show(None<int>()));
      });
    });
    Describe("in the case of type Some", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        AssertEquals(OptionType::SOME, Some(42).GetType());
      });
      It("should evalute the Some case when calling Match()", []() {
        auto result = Match(Some(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
        AssertTrue(result);
      });
      It("should return true when calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, Some(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, Some(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(Some(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(Some(42)));
      });
      It("should return false when called with Equals() and a none", []() {
        AssertTrue(IsEmpty(None<int>()));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(Some(42), None<int>()));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(Some(42), Some(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(Some(42) == None<int>());
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(Some(42) == Some(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(Some(42) == Some(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(Some(42) != None<int>());
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(Some(42) != Some(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(Some(42) != Some(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(Some<int>(42)));
      });
      It("should return itself when called with Add() and a None()", []() {
        AssertEquals(Some(42), Add(Some(42), None<int>()));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(Some(48), Add(Some(42), Some(6)));
      });
      It("should return itself when called with + and a None()", []() {
        AssertEquals(Some(42), Some(42) + None<int>());
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(Some(48), Some(42) + Some(6));
      });
      It("should return None() when called with Filter() and a non match predicate", []() {
        AssertEquals(None<int>(), Filter(Equals(12), Some(42)));
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        AssertEquals(Some(42), Filter(Equals(42), Some(42)));
      });
      It("should return GREATER when called with Compare() and a None()", []() {
        AssertEquals(Ordering::GREATER, Compare(Some(42), None<int>()));
      });
      It("should return GREATER when called with Compare() and a lesser Some()", []() {
        AssertEquals(Ordering::GREATER, Compare(Some(42), Some(8)));
      });
      It("should return EQUAL when called with Compare() and an equal Some()", []() {
        AssertEquals(Ordering::EQUAL, Compare(Some(42), Some(42)));
      });
      It("should return LESS when called with Compare() and a greater Some()", []() {
        AssertEquals(Ordering::LESS, Compare(Some(42), Some(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(Some(84), Map(Multiply(2), Some(42)));
      });
      It("should return itself when called with Alt() and another Some()", []() {
        AssertEquals(Some(42), Alt(Some(42), Some(12)));
      });
      It("should return itself when called with Alt() and a None()", []() {
        AssertEquals(Some(42), Alt(Some(42), None<int>()));
      });
      It("should return itself when compared with || and another Some()", []() {
        AssertEquals(Some(42), Some(42) || Some(12));
      });
      It("should return itself when compared with || and None()", []() {
        AssertEquals(Some(42), Some(42) || None<int>());
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(None<int>(), FlatMap([](auto n) { return None<int>(); }, Some(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(Some(84), FlatMap([](auto n) { return Some(n * 2); }, Some(42)));
      });
      It("should return the next Some(n) when called with Then()", []() {
        AssertEquals(Some(42), Then(Some(12), Some(42)));
      });
      It("should return None() when called with Then() and a LocalNone()", []() {
        AssertEquals(None<int>(), Then(Some(42), None<int>()));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(Some(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), Some(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, Some(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, Some(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, Some(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, Some(42)));
      });
      It("should return the string 'Some(n)' when called with Show()", []() {
        AssertEquals(String("Some(42)"), Show(Some(42)));
      });
    });
  });
}

}