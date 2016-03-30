#pragma once

#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/option.h"

namespace traitorous {

void SharedOptionSpecification() {
  Describe("A SharedOption type", []() {
    It("should have a zero value of SharedNone()", []() {
      AssertEquals(SharedNone<int>(), Zero<SharedOption<int>>());
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        AssertEquals(OptionType::NONE, SharedNone<int>()->GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(SharedNone<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, SharedNone<int>()));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(SharedNone<int>()));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(SharedNone<int>()));
      });
      It("should return true when called with Equals() and another none", []() {
        AssertTrue(Equals(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return false when called with Equals() and a SharedSome()", []() {
        AssertFalse(Equals(SharedNone<int>(), SharedSome(42)));
      });
      It("should return true when compared with == and another none", []() {
        AssertTrue(SharedNone<int>() == SharedNone<int>());
      });
      It("should return false when compared with == and a SharedSome()", []() {
        AssertFalse(SharedNone<int>() == SharedSome(42));
      });
      It("should return false when compared with != and another none", []() {
        AssertFalse(SharedNone<int>() != SharedNone<int>());
      });
      It("should return true when compared with != a SharedSome()", []() {
        AssertTrue(SharedNone<int>() != SharedSome(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(SharedNone<int>()));
      });
      It("should return none when called with Add() and another SharedNone()", []() {
        AssertEquals(SharedNone<int>(), Add(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return SharedSome(n) when called with Add() and a SharedSome(n)", []() {
        AssertEquals(SharedSome(42), Add(SharedNone<int>(), SharedSome(42)));
      });
      It("should return SharedNone() when called with Filter()", []() {
        AssertEquals(SharedNone<int>(), Filter(Equals(42), SharedNone<int>()));
      });
      It("should return LESS when passed through Compare() with SharedSome()", []() {
        AssertEquals(Ordering::LESS, Compare(SharedNone<int>(), SharedSome(42)));
      });
      It("should return EQUAL when passed through Compare() with another SharedNone()", []() {
        AssertEquals(Ordering::EQUAL, Compare(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return SharedNone() when passed through Map()", []() {
        AssertEquals(SharedNone<int>(), Map(Multiply(2), SharedNone<int>()));
      });
      It("should return None() when passed through Alt() with another SharedNone()", []() {
        AssertEquals(SharedNone<int>(), Alt(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return SharedSome(n) when passed through Alt() with SharedSome(n)", []() {
        AssertEquals(SharedSome(42), Alt(SharedNone<int>(), SharedSome(42)));
      });
      It("should return None() when passed through || with another SharedNone()", []() {
        AssertEquals(SharedNone<int>(), SharedNone<int>() || SharedNone<int>());
      });
      It("should return SharedSome(n) when passed through || with SharedSome(n)", []() {
        AssertEquals(SharedSome(42), SharedNone<int>() || SharedSome(42));
      });
      It("should return SharedNone() when called with FlatMap()", []() {
        AssertEquals(SharedNone<int>(), FlatMap([](auto n) { return SharedSome(n * 2); }, SharedNone<int>()));
      });
      It("should return SharedNone() when called with Then() and another none", []() {
        AssertEquals(SharedNone<int>(), Then(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return SharedNone() when called with Then() and a SharedSome()", []() {
        AssertEquals(SharedNone<int>(), Then(SharedNone<int>(), SharedSome(42)));
      });
      It("should return SharedNone() when called with MPlus() and another None()", []() {
        AssertEquals(SharedNone<int>(), MPlus(SharedNone<int>(), SharedNone<int>()));
      });
      It("should return SharedSome(n) when called with MPlus() and another SharedSome(n)", []() {
        AssertEquals(SharedSome(42), MPlus(SharedNone<int>(), SharedSome(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(SharedNone<int>()));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), SharedNone<int>()));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, SharedNone<int>()));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, SharedNone<int>()));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, SharedNone<int>()));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, SharedNone<int>()));
      });
      It("should return the string 'none' when called with Show()", []() {
        AssertEquals(String("SharedNone"), Show(SharedNone<int>()));
      });
    });
    Describe("in the case of type SharedSome", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        AssertEquals(OptionType::SOME, SharedSome(42)->GetType());
      });
      It("should evalute the SharedSome case when calling Match()", []() {
        auto result = Match(SharedSome(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
        AssertTrue(result);
      });
      It("should return true when calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, SharedSome(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, SharedSome(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(SharedSome(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(SharedSome(42)));
      });
      It("should return false when called with Equals() and a none", []() {
        AssertTrue(IsEmpty(SharedNone<int>()));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(SharedSome(42), SharedNone<int>()));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(SharedSome(42), SharedSome(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(SharedSome(42) == SharedNone<int>());
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(SharedSome(42) == SharedSome(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(SharedSome(42) == SharedSome(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(SharedSome(42) != SharedNone<int>());
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(SharedSome(42) != SharedSome(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(SharedSome(42) != SharedSome(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(SharedSome<int>(42)));
      });
      It("should return itself when called with Add() and a SharedNone()", []() {
        AssertEquals(SharedSome(42), Add(SharedSome(42), SharedNone<int>()));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(SharedSome(48), Add(SharedSome(42), SharedSome(6)));
      });
      It("should return itself when called with + and a SharedNone()", []() {
        AssertEquals(SharedSome(42), SharedSome(42) + SharedNone<int>());
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(SharedSome(48), SharedSome(42) + SharedSome(6));
      });
      It("should return SharedNone() when called with Filter() and a non match predicate", []() {
        AssertEquals(SharedNone<int>(), Filter(Equals(12), SharedSome(42)));
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        AssertEquals(SharedSome(42), Filter(Equals(42), SharedSome(42)));
      });
      It("should return GREATER when called with Compare() and a SharedNone()", []() {
        AssertEquals(Ordering::GREATER, Compare(SharedSome(42), SharedNone<int>()));
      });
      It("should return GREATER when called with Compare() and a lesser SharedSome()", []() {
        AssertEquals(Ordering::GREATER, Compare(SharedSome(42), SharedSome(8)));
      });
      It("should return EQUAL when called with Compare() and an equal SharedSome()", []() {
        AssertEquals(Ordering::EQUAL, Compare(SharedSome(42), SharedSome(42)));
      });
      It("should return LESS when called with Compare() and a greater SharedSome()", []() {
        AssertEquals(Ordering::LESS, Compare(SharedSome(42), SharedSome(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(SharedSome(84), Map(Multiply(2), SharedSome(42)));
      });
      It("should return itself when called with Alt() and another SharedSome()", []() {
        AssertEquals(SharedSome(42), Alt(SharedSome(42), SharedSome(12)));
      });
      It("should return itself when called with Alt() and a SharedNone()", []() {
        AssertEquals(SharedSome(42), Alt(SharedSome(42), SharedNone<int>()));
      });
      It("should return itself when compared with || and another SharedSome()", []() {
        AssertEquals(SharedSome(42), SharedSome(42) || SharedSome(12));
      });
      It("should return itself when compared with || and SharedNone()", []() {
        AssertEquals(SharedSome(42), SharedSome(42) || SharedNone<int>());
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(SharedNone<int>(), FlatMap([](auto n) { return SharedNone<int>(); }, SharedSome(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(SharedSome(84), FlatMap([](auto n) { return SharedSome(n * 2); }, SharedSome(42)));
      });
      It("should return the next SharedSome(n) when called with Then()", []() {
        AssertEquals(SharedSome(42), Then(SharedSome(12), SharedSome(42)));
      });
      It("should return SharedNone() when called with Then() and a None()", []() {
        AssertEquals(SharedNone<int>(), Then(SharedSome(42), SharedNone<int>()));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(SharedSome(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), SharedSome(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, SharedSome(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, SharedSome(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, SharedSome(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, SharedSome(42)));
      });
      It("should return the string 'SharedSome(n)' when called with Show()", []() {
        AssertEquals(String("SharedSome(42)"), Show(SharedSome(42)));
      });
    });
  });
}

}