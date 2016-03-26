#ifndef TRAITOROUS_LOCAL_OPTION_SPEC_H
#define TRAITOROUS_LOCAL_OPTION_SPEC_H

#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/option.h"

namespace traitorous {

void LocalOptionSpecification() {
  Describe("A LocalOption type", []() {
    It("should have a zero value of LocalNone()", []() {
      AssertEquals(LocalNone<int>(), Zero<LocalOption<int>>());
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        AssertEquals(OptionType::NONE, LocalNone<int>().GetType());
      });
      It("should evalute the none case when calling Match()", []() {
        auto result = Match(LocalNone<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
        AssertTrue(result);
      });
      It("should return false when called with Contains()", []() {
        AssertFalse(Contains(42, LocalNone<int>()));
      });
      It("should return 0 when called with Length()", []() {
        AssertEquals((size_t) 0, Length(LocalNone<int>()));
      });
      It("should return true when called with IsEmpty()", []() {
        AssertTrue(IsEmpty(LocalNone<int>()));
      });
      It("should return true when called with Equals() and another none", []() {
        AssertTrue(Equals(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return false when called with Equals() and a LocalSome()", []() {
        AssertFalse(Equals(LocalNone<int>(), LocalSome(42)));
      });
      It("should return true when compared with == and another none", []() {
        AssertTrue(LocalNone<int>() == LocalNone<int>());
      });
      It("should return false when compared with == and a LocalSome()", []() {
        AssertFalse(LocalNone<int>() == LocalSome(42));
      });
      It("should return false when compared with != and another none", []() {
        AssertFalse(LocalNone<int>() != LocalNone<int>());
      });
      It("should return true when compared with != a LocalSome()", []() {
        AssertTrue(LocalNone<int>() != LocalSome(42));
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        AssertEquals(0, Hash(LocalNone<int>()));
      });
      It("should return none when called with Add() and another LocalNone()", []() {
        AssertEquals(LocalNone<int>(), Add(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return LocalSome(n) when called with Add() and a LocalSome(n)", []() {
        AssertEquals(LocalSome(42), Add(LocalNone<int>(), LocalSome(42)));
      });
      It("should return LocalNone() when called with Filter()", []() {
        AssertEquals(LocalNone<int>(), Filter(Equals(42), LocalNone<int>()));
      });
      It("should return LESS when passed through Compare() with LocalSome()", []() {
        AssertEquals(LESS, Compare(LocalNone<int>(), LocalSome(42)));
      });
      It("should return EQUAL when passed through Compare() with another LocalNone()", []() {
        AssertEquals(EQUAL, Compare(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return LocalNone() when passed through Map()", []() {
        AssertEquals(LocalNone<int>(), Map(Multiply(2), LocalNone<int>()));
      });
      It("should return LocalNone() when passed through Alt() with another LocalNone()", []() {
        AssertEquals(LocalNone<int>(), Alt(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return LocalSome(n) when passed through Alt() with LocalSome(n)", []() {
        AssertEquals(LocalSome(42), Alt(LocalNone<int>(), LocalSome(42)));
      });
      It("should return LocalNone() when passed through || with another LocalNone()", []() {
        AssertEquals(LocalNone<int>(), LocalNone<int>() || LocalNone<int>());
      });
      It("should return LocalSome(n) when passed through || with LocalSome(n)", []() {
        AssertEquals(LocalSome(42), LocalNone<int>() || LocalSome(42));
      });
      It("should return LocalNone() when called with FlatMap()", []() {
        AssertEquals(LocalNone<int>(), FlatMap([](auto n) { return LocalSome(n * 2); }, LocalNone<int>()));
      });
      It("should return LocalNone() when called with Then() and another none", []() {
        AssertEquals(LocalNone<int>(), Then(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return LocalNone() when called with Then() and a LocalSome()", []() {
        AssertEquals(LocalNone<int>(), Then(LocalNone<int>(), LocalSome(42)));
      });
      It("should return LocalNone() when called with MPlus() and another LocalNone()", []() {
        AssertEquals(LocalNone<int>(), MPlus(LocalNone<int>(), LocalNone<int>()));
      });
      It("should return LocalSome(n) when called with MPlus() and another LocalSome(n)", []() {
        AssertEquals(LocalSome(42), MPlus(LocalNone<int>(), LocalSome(42)));
      });
      It("should return zero when called with Fold()", []() {
        AssertEquals(0, Fold(LocalNone<int>()));
      });
      It("should return zero when called with foldMap()", []() {
        AssertEquals(0, FoldMap(Identity<int>(), LocalNone<int>()));
      });
      It("should return init when called with FoldR()", []() {
        AssertEquals(0, FoldR(Add<int>(), 0, LocalNone<int>()));
      });
      It("should return init when called with FoldL()", []() {
        AssertEquals(0, FoldL(Add<int>(), 0, LocalNone<int>()));
      });
      It("should return the alternative when called with GetOrElse()", []() {
        AssertEquals(12, GetOrElse([]() { return 12; }, LocalNone<int>()));
      });
      It("should return the default when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(42, LocalNone<int>()));
      });
      It("should return the string 'none' when called with Show()", []() {
        AssertEquals(LocalString("LocalNone"), Show(LocalNone<int>()));
      });
    });
    Describe("in the case of type LocalSome", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        AssertEquals(OptionType::SOME, LocalSome(42).GetType());
      });
      It("should evalute the LocalSome case when calling Match()", []() {
        auto result = Match(LocalSome(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
        AssertTrue(result);
      });
      It("should return true when calling Contains() with a matching item", []() {
        AssertTrue(Contains(42, LocalSome(42)));
      });
      It("should return false when calling Contains() with a different item", []() {
        AssertFalse(Contains(12, LocalSome(42)));
      });
      It("should return 1 when called with Length()", []() {
        AssertEquals((size_t) 1, Length(LocalSome(42)));
      });
      It("should return false when called with is_empty", []() {
        AssertFalse(IsEmpty(LocalSome(42)));
      });
      It("should return false when called with Equals() and a none", []() {
        AssertTrue(IsEmpty(LocalNone<int>()));
      });
      It("should return false when called with Equals() and a different item", []() {
        AssertFalse(Equals(LocalSome(42), LocalNone<int>()));
      });
      It("should return true when called with Equals() and a matching item", []() {
        AssertTrue(Equals(LocalSome(42), LocalSome(42)));
      });
      It("should return false when compared with == and a none", []() {
        AssertFalse(LocalSome(42) == LocalNone<int>());
      });
      It("should return false when compared with == and a different item", []() {
        AssertFalse(LocalSome(42) == LocalSome(12));
      });
      It("should return true when compared with == with a matching item", []() {
        AssertTrue(LocalSome(42) == LocalSome(42));
      });
      It("should return true when compared with != and a none", []() {
        AssertTrue(LocalSome(42) != LocalNone<int>());
      });
      It("should return true when compared with != and a different item", []() {
        AssertTrue(LocalSome(42) != LocalSome(12));
      });
      It("should return false when compared with != and a matching item", []() {
        AssertFalse(LocalSome(42) != LocalSome(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        AssertEquals(Hash(42), Hash(LocalSome<int>(42)));
      });
      It("should return itself when called with Add() and a LocalNone()", []() {
        AssertEquals(LocalSome(42), Add(LocalSome(42), LocalNone<int>()));
      });
      It("should return the sum of values when called with Add() and a value", []() {
        AssertEquals(LocalSome(48), Add(LocalSome(42), LocalSome(6)));
      });
      It("should return itself when called with + and a LocalNone()", []() {
        AssertEquals(LocalSome(42), LocalSome(42) + LocalNone<int>());
      });
      It("should return the sum of values when called with + and a value", []() {
        AssertEquals(LocalSome(48), LocalSome(42) + LocalSome(6));
      });
      It("should return LocalNone() when called with Filter() and a non match predicate", []() {
        AssertEquals(LocalNone<int>(), Filter(Equals(12), LocalSome(42)));
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        AssertEquals(LocalSome(42), Filter(Equals(42), LocalSome(42)));
      });
      It("should return GREATER when called with Compare() and a LocalNone()", []() {
        AssertEquals(GREATER, Compare(LocalSome(42), LocalNone<int>()));
      });
      It("should return GREATER when called with Compare() and a lesser LocalSome()", []() {
        AssertEquals(GREATER, Compare(LocalSome(42), LocalSome(8)));
      });
      It("should return EQUAL when called with Compare() and an equal LocalSome()", []() {
        AssertEquals(EQUAL, Compare(LocalSome(42), LocalSome(42)));
      });
      It("should return LESS when called with Compare() and a greater LocalSome()", []() {
        AssertEquals(LESS, Compare(LocalSome(42), LocalSome(100)));
      });
      It("should return n * 2 when called with Map(*2)", []() {
        AssertEquals(LocalSome(84), Map(Multiply(2), LocalSome(42)));
      });
      It("should return itself when called with Alt() and another LocalSome()", []() {
        AssertEquals(LocalSome(42), Alt(LocalSome(42), LocalSome(12)));
      });
      It("should return itself when called with Alt() and a LocalNone()", []() {
        AssertEquals(LocalSome(42), Alt(LocalSome(42), LocalNone<int>()));
      });
      It("should return itself when compared with || and another LocalSome()", []() {
        AssertEquals(LocalSome(42), LocalSome(42) || LocalSome(12));
      });
      It("should return itself when compared with || and LocalNone()", []() {
        AssertEquals(LocalSome(42), LocalSome(42) || LocalNone<int>());
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        AssertEquals(LocalNone<int>(), FlatMap([](auto n) { return LocalNone<int>(); }, LocalSome(42)));
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        AssertEquals(LocalSome(84), FlatMap([](auto n) { return LocalSome(n * 2); }, LocalSome(42)));
      });
      It("should return the next LocalSome(n) when called with Then()", []() {
        AssertEquals(LocalSome(42), Then(LocalSome(12), LocalSome(42)));
      });
      It("should return LocalNone() when called with Then() and a LocalNone()", []() {
        AssertEquals(LocalNone<int>(), Then(LocalSome(42), LocalNone<int>()));
      });
      It("should return the inner value when called with Fold()", []() {
        AssertEquals(42, Fold(LocalSome(42)));
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        AssertEquals(42, FoldMap(Identity<int>(), LocalSome(42)));
      });
      It("should return the folded value when called with FoldR()", []() {
        AssertEquals(54, FoldR(Add<int>(), 12, LocalSome(42)));
      });
      It("should return the folded value when called with FoldL()", []() {
        AssertEquals(54, FoldL(Add<int>(), 12, LocalSome(42)));
      });
      It("should return the inner value when called with GetOrElse()", []() {
        AssertEquals(42, GetOrElse([]() { return 12; }, LocalSome(42)));
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        AssertEquals(42, GetOrDefault(12, LocalSome(42)));
      });
      It("should return the string 'LocalSome(n)' when called with Show()", []() {
        AssertEquals(LocalString("LocalSome(42)"), Show(LocalSome(42)));
      });
    });
  });
}

}

#endif
