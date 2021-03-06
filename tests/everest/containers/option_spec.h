#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/option.h>
#include <everest/containers/option/all_traits.h>
#include <everest/types/int32.h>
#include <everest/functions/identity.h>
#include <everest/types/expressive/hash_value/eq.h>
#include <everest/types/expressive/hash_value/show.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>
#include <everest/pointer/traits/all_traits.h>

namespace everest {

void OptionSpecification() {
  Describe("A Option type", []() {
    It("should have a zero value of None()", []() {
      AssertEquals(Option<int>::None(), Option<int>::Zero());
    });
    It("should return a None() when passed a nullptr", []() {
      AssertEquals(Option<int*>::None(), Option<int*>(nullptr));
    });
    It("should return a Some() when passed a non nullptr", []() {
      auto stackRef = 1;
      AssertEquals(Option<int*>::Some(&stackRef), Option<int*>(&stackRef));
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        AssertEquals(OptionType::NONE, Option<int>::None().GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Option<int>::None().Match(
          []()       { return true; },
          [](auto n) { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, Option<int>::None()));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(Option<int>::None()));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(Option<int>::None()));
      });
      It("should return true when called with Equals() and another none", []() {
        AssertTrue(Equals(Option<int>::None(), Option<int>::None()));
      });
      It("should return false when called with Equals() and a Some()", []() {
        AssertFalse(Equals(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return true when compared with == and another none", []() {
        AssertTrue(Option<int>::None() == Option<int>::None());
      });
      It("should return false when compared with == and a Some()", []() {
        AssertFalse(Option<int>::None() == Option<int>::Some(42));
      });
      It("should return false when compared with != and another none", []() {
        AssertFalse(Option<int>::None() != Option<int>::None());
      });
      It("should return true when compared with != a Some()", []() {
        AssertTrue(Option<int>::None() != Option<int>::Some(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(HashValue(0u), Hash(Option<int>::None()));
      });
      It("should return none when called with Add() and another None()", []() {
        AssertEquals(Option<int>::None(), Add(Option<int>::None(), Option<int>::None()));
      });
      It("should return Some(n) when called with Add() and a Some(n)", []() {
        AssertEquals(Option<int>::Some(42), Add(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return None() when called with Filter()", []() {
        AssertEquals(Option<int>::None(), Filter(Equals(42), Option<int>::None()));
      });
      It("should return LESS when passed through Compare() with Some()", []() {
        AssertEquals(Ordering::LESS, Compare(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return EQUAL when passed through Compare() with another None()", []() {
        AssertEquals(Ordering::EQUAL, Compare(Option<int>::None(), Option<int>::None()));
      });
      It("should return None() when passed through Map()", []() {
        AssertEquals(Option<int>::None(), Map(Multiply(2), Option<int>::None()));
      });
      It("should return LocalNone() when passed through Alt() with another None()", []() {
        AssertEquals(Option<int>::None(), Alt(Option<int>::None(), Option<int>::None()));
      });
      It("should return Some(n) when passed through Alt() with Some(n)", []() {
        AssertEquals(Option<int>::Some(42), Alt(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return LocalNone() when passed through || with another None()", []() {
        AssertEquals(Option<int>::None(), Option<int>::None() || Option<int>::None());
      });
      It("should return Some(n) when passed through || with Some(n)", []() {
        AssertEquals(Option<int>::Some(42), Option<int>::None() || Option<int>::Some(42));
      });
      It("should return None() when called with FlatMap()", []() {
        AssertEquals(Option<int>::None(), FlatMap([](auto n) { return Option<int>::Some(n * 2); }, Option<int>::None()));
      });
      It("should return None() when called with Then() and another none", []() {
        AssertEquals(Option<int>::None(), Then(Option<int>::None(), Option<int>::None()));
      });
      It("should return None() when called with Then() and a Some()", []() {
        AssertEquals(Option<int>::None(), Then(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return None() when called with MPlus() and another LocalNone()", []() {
        AssertEquals(Option<int>::None(), MPlus(Option<int>::None(), Option<int>::None()));
      });
      It("should return Some(n) when called with MPlus() and another Some(n)", []() {
        AssertEquals(Option<int>::Some(42), MPlus(Option<int>::None(), Option<int>::Some(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(Option<int>::None()));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), Option<int>::None()));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, Option<int>::None()));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, Option<int>::None()));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, Option<int>::None()));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, Option<int>::None()));
      });
      It("should return the mutable_string 'none' when called with Show()", []() {
        AssertEquals(String("None"), Show(Option<int>::None()));
      });
    });
    Describe("in the case of type Some", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        AssertEquals(OptionType::SOME, Option<int>::Some(42).GetType());
      });
      It("should evalute the Some case when calling Match()", []() {
        auto result = Option<int>::Some(42).Match(
          []()       { return false; },
          [](auto n) { return true; }
        );
        AssertTrue(result);
      });
      It("should return true when calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, Option<int>::Some(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, Option<int>::Some(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(Option<int>::Some(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(Option<int>::Some(42)));
      });
      It("should return false when called with Equals() and a none", []() {
        AssertTrue(IsEmpty(Option<int>::None()));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(Option<int>::Some(42), Option<int>::None()));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(Option<int>::Some(42), Option<int>::Some(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(Option<int>::Some(42) == Option<int>::None());
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(Option<int>::Some(42) == Option<int>::Some(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(Option<int>::Some(42) == Option<int>::Some(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(Option<int>::Some(42) != Option<int>::None());
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(Option<int>::Some(42) != Option<int>::Some(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(Option<int>::Some(42) != Option<int>::Some(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(Option<int>::Some(42)));
      });
      It("should return itself when called with Add() and a None()", []() {
        AssertEquals(Option<int>::Some(42), Add(Option<int>::Some(42), Option<int>::None()));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(Option<int>::Some(48), Add(Option<int>::Some(42), Option<int>::Some(6)));
      });
      It("should return itself when called with + and a None()", []() {
        AssertEquals(Option<int>::Some(42), Option<int>::Some(42) + Option<int>::None());
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(Option<int>::Some(48), Option<int>::Some(42) + Option<int>::Some(6));
      });
      It("should return None() when called with Filter() and a non match predicate", []() {
        AssertEquals(Option<int>::None(), Filter(Equals(12), Option<int>::Some(42)));
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        AssertEquals(Option<int>::Some(42), Filter(Equals(42), Option<int>::Some(42)));
      });
      It("should return GREATER when called with Compare() and a None()", []() {
        AssertEquals(Ordering::GREATER, Compare(Option<int>::Some(42), Option<int>::None()));
      });
      It("should return GREATER when called with Compare() and a lesser Some()", []() {
        AssertEquals(Ordering::GREATER, Compare(Option<int>::Some(42), Option<int>::Some(8)));
      });
      It("should return EQUAL when called with Compare() and an equal Some()", []() {
        AssertEquals(Ordering::EQUAL, Compare(Option<int>::Some(42), Option<int>::Some(42)));
      });
      It("should return LESS when called with Compare() and a greater Some()", []() {
        AssertEquals(Ordering::LESS, Compare(Option<int>::Some(42), Option<int>::Some(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(Option<int>::Some(84), Map(Multiply(2), Option<int>::Some(42)));
      });
      It("should return itself when called with Alt() and another Option<int>::Some()", []() {
        AssertEquals(Option<int>::Some(42), Alt(Option<int>::Some(42), Option<int>::Some(12)));
      });
      It("should return itself when called with Alt() and a None()", []() {
        AssertEquals(Option<int>::Some(42), Alt(Option<int>::Some(42), Option<int>::None()));
      });
      It("should return itself when compared with || and another Option<int>::Some()", []() {
        AssertEquals(Option<int>::Some(42), Option<int>::Some(42) || Option<int>::Some(12));
      });
      It("should return itself when compared with || and None()", []() {
        AssertEquals(Option<int>::Some(42), Option<int>::Some(42) || Option<int>::None());
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(Option<int>::None(), FlatMap([](auto n) { return Option<int>::None(); }, Option<int>::Some(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(Option<int>::Some(84), FlatMap([](auto n) { return Option<int>::Some(n * 2); }, Option<int>::Some(42)));
      });
      It("should return the next Option<int>::Some(n) when called with Then()", []() {
        AssertEquals(Option<int>::Some(42), Then(Option<int>::Some(12), Option<int>::Some(42)));
      });
      It("should return None() when called with Then() and a LocalNone()", []() {
        AssertEquals(Option<int>::None(), Then(Option<int>::Some(42), Option<int>::None()));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(Option<int>::Some(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), Option<int>::Some(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, Option<int>::Some(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, Option<int>::Some(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, Option<int>::Some(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, Option<int>::Some(42)));
      });
      It("should return the mutable_string 'Option<int>::Some(n)' when called with Show()", []() {
        AssertEquals(String("Some(42)"), Show(Option<int>::Some(42)));
      });
    });
  });
}

}