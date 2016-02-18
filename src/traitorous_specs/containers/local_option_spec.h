#ifndef TRAITOROUS_LOCAL_OPTION_SPEC_H
#define TRAITOROUS_LOCAL_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/local_option.h"
#include "functions/identity.h"

namespace traitorous {

void LocalOptionSpecification() {
  Describe("A LocalOption type", []() {
    It("should have a zero value of None()", []() {
      return Zero<LocalOption<int>>() == LocalNone<int>();
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        return LocalNone<int>().GetType() == OPTION_NONE;
      });
      It("should evalute the none case when calling Match()", []() {
        return Match(LocalNone<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
      });
      It("should return false when called with Contains()", []() {
        return !Contains(42, LocalNone<int>());
      });
      It("should return 0 when called with Length()", []() {
        return Length(LocalNone<int>()) == 0;
      });
      It("should return true when called with IsEmpty()", []() {
        return IsEmpty(LocalNone<int>());
      });
      It("should return true when called with Equals() and another none", []() {
        return Equals(LocalNone<int>(), LocalNone<int>());
      });
      It("should return false when called with Equals() and a LocalSome()", []() {
        return !Equals(LocalNone<int>(), LocalSome(42));
      });
      It("should return true when compared with == and another none", []() {
        return LocalNone<int>() == LocalNone<int>();
      });
      It("should return false when compared with == and a LocalSome()", []() {
        return !(LocalNone<int>() == LocalSome(42));
      });
      It("should return false when compared with != and another none", []() {
        return !(LocalNone<int>() != LocalNone<int>());
      });
      It("should return true when compared with != a LocalSome()", []() {
        return LocalNone<int>() != LocalSome(42);
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        return Hash(LocalNone<int>()) == 0;
      });
      It("should return none when called with Add() and another None()", []() {
        return Add(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return LocalSome(n) when called with Add() and a LocalSome(n)", []() {
        return Add(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      It("should return None() when called with Filter()", []() {
        return Filter(Equals(42), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return LESS when passed through Compare() with LocalSome()", []() {
        return Compare(LocalNone<int>(), LocalSome(42)) == LESS;
      });
      It("should return EQUAL when passed through Compare() with another None()", []() {
        return Compare(LocalNone<int>(), LocalNone<int>()) == EQUAL;
      });
      It("should return None() when passed through Map()", []() {
        return Map(Multiply(2), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return None() when passed through Alt() with another None()", []() {
        return Alt(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return LocalSome(n) when passed through Alt() with LocalSome(n)", []() {
        return Alt(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      It("should return None() when passed through || with another None()", []() {
        return (LocalNone<int>() || LocalNone<int>()) == LocalNone<int>();
      });
      It("should return LocalSome(n) when passed through || with LocalSome(n)", []() {
        return (LocalNone<int>() || LocalSome(42)) == LocalSome(42);
      });
      It("should return None() when called with FlatMap()", []() {
        return FlatMap([](auto n) { return LocalSome(n * 2); }, LocalNone<int>()) == LocalNone<int>();
      });
      It("should return None() when called with Then() and another none", []() {
        return Then(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return None() when called with Then() and a LocalSome()", []() {
        return Then(LocalNone<int>(), LocalSome(42)) == LocalNone<int>();
      });
      It("should return None() when called with MPlus() and another None()", []() {
        return MPlus(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return LocalSome(n) when called with MPlus() and another LocalSome(n)", []() {
        return MPlus(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      It("should return zero when called with Fold()", []() {
        return Fold(LocalNone<int>()) == 0;
      });
      It("should return zero when called with foldMap()", []() {
        return FoldMap(Identity<int>(), LocalNone<int>()) == 0;
      });
      It("should return init when called with FoldR()", []() {
        return FoldR(Add<int>(), 0, LocalNone<int>()) == 0;
      });
      It("should return init when called with FoldL()", []() {
        return FoldL(Add<int>(), 0, LocalNone<int>()) == 0;
      });
      It("should return the alternative when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalNone<int>()) == 12;
      });
      It("should return the default when called with GetOrDefault()", []() {
        return GetOrDefault(42, LocalNone<int>()) == 42;
      });
      It("should return the string 'none' when called with Show()", []() {
        return Show(LocalNone<int>()) == std::string("LocalNone");
      });
    });
    Describe("in the case of type LocalSome", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        return LocalSome(42).GetType() == OPTION_SOME;
      });
      It("should evalute the LocalSome case when calling Match()", []() {
        return Match(LocalSome(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
      });
      It("should return true when calling Contains() with a matching item", []() {
        return Contains(42, LocalSome(42));
      });
      It("should return false when calling Contains() with a different item", []() {
        return !Contains(12, LocalSome(42));
      });
      It("should return 1 when called with Length()", []() {
        return Length(LocalSome(42)) == 1;
      });
      It("should return false when called with is_empty", []() {
        return !IsEmpty(LocalSome(42));
      });
      It("should return false when called with Equals() and a none", []() {
        return IsEmpty(LocalNone<int>());
      });
      It("should return false when called with Equals() and a different item", []() {
        return !Equals(LocalSome(42), LocalNone<int>());
      });
      It("should return true when called with Equals() and a matching item", []() {
        return Equals(LocalSome(42), LocalSome(42));
      });
      It("should return false when compared with == and a none", []() {
        return !(LocalSome(42) == LocalNone<int>());
      });
      It("should return false when compared with == and a different item", []() {
        return !(LocalSome(42) == LocalSome(12));
      });
      It("should return true when compared with == with a matching item", []() {
        return LocalSome(42) == LocalSome(42);
      });
      It("should return true when compared with != and a none", []() {
        return LocalSome(42) != LocalNone<int>();
      });
      It("should return true when compared with != and a different item", []() {
        return LocalSome(42) != LocalSome(12);
      });
      It("should return false when compared with != and a matching item", []() {
        return !(LocalSome(42) != LocalSome(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        return Hash(LocalSome<int>(42)) == Hash(42);
      });
      It("should return itself when called with Add() and a None()", []() {
        return Add(LocalSome(42), LocalNone<int>()) == LocalSome(42);
      });
      It("should return the sum of values when called with Add() and a value", []() {
        return Add(LocalSome(42), LocalSome(6)) == LocalSome(48);
      });
      It("should return itself when called with + and a None()", []() {
        return (LocalSome(42) + LocalNone<int>()) == LocalSome(42);
      });
      It("should return the sum of values when called with + and a value", []() {
        return (LocalSome(42) + LocalSome(6)) == LocalSome(48);
      });
      It("should return None() when called with Filter() and a non match predicate", []() {
        return Filter(Equals(12), LocalSome(42)) == LocalNone<int>();
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        return Filter(Equals(42), LocalSome(42)) == LocalSome(42);
      });
      It("should return GREATER when called with Compare() and a None()", []() {
        return Compare(LocalSome(42), LocalNone<int>()) == GREATER;
      });
      It("should return GREATER when called with Compare() and a lesser LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(8)) == GREATER;
      });
      It("should return EQUAL when called with Compare() and an equal LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(42)) == EQUAL;
      });
      It("should return LESS when called with Compare() and a greater LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(100)) == LESS;
      });
      It("should return n * 2 when called with Map(*2)", []() {
        return Map(Multiply(2), LocalSome(42)) == LocalSome(84);
      });
      It("should return itself when called with Alt() and another LocalSome()", []() {
        return Alt(LocalSome(42), LocalSome(12)) == LocalSome(42);
      });
      It("should return itself when called with Alt() and a None()", []() {
        return Alt(LocalSome(42), LocalNone<int>()) == LocalSome(42);
      });
      It("should return itself when compared with || and another LocalSome()", []() {
        return (LocalSome(42) || LocalSome(12)) == LocalSome(42);
      });
      It("should return itself when compared with || and None()", []() {
        return (LocalSome(42) || LocalNone<int>()) == LocalSome(42);
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        return FlatMap([](auto n) { return LocalNone<int>(); }, LocalSome(42)) == LocalNone<int>();
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        return FlatMap([](auto n) { return LocalSome(n * 2); }, LocalSome(42)) == LocalSome(84);
      });
      It("should return the next LocalSome(n) when called with Then()", []() {
        return Then(LocalSome(12), LocalSome(42)) == LocalSome(42);
      });
      It("should return None() when called with Then() and a None()", []() {
        return Then(LocalSome(42), LocalNone<int>()) == LocalNone<int>();
      });
      It("should return the inner value when called with Fold()", []() {
        return Fold(LocalSome(42)) == 42;
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        return FoldMap(Identity<int>(), LocalSome(42)) == 42;
      });
      It("should return the folded value when called with FoldR()", []() {
        return FoldR(Add<int>(), 12, LocalSome(42)) == 54;
      });
      It("should return the folded value when called with FoldL()", []() {
        return FoldL(Add<int>(), 12, LocalSome(42)) == 54;
      });
      It("should return the inner value when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalSome(42)) == 42;
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        return GetOrDefault(12, LocalSome(42)) == 42;
      });
      It("should return the string 'LocalSome(n)' when called with Show()", []() {
        return Show(LocalSome(42)) == std::string("LocalSome(42)");
      });
    });
  });
}

}

#endif
