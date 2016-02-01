#ifndef TRAITOROUS_OPTION_SPEC_H
#define TRAITOROUS_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/option.h"
#include "functions/identity.h"

namespace traitorous {

void OptionSpecification() {
  Describe("A Option type", []() {
    It("should have a zero value of None()", []() {
      return Zero<Option<int>>() == None<int>();
    });
    Describe("in the case of type none", []() {
      It("should return OPTION_NONE when calling get_type()", []() {
        return None<int>()->GetType() == OPTION_NONE;
      });
      It("should evalute the none case when calling Match()", []() {
        return Match(None<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
      });
      It("should return false when called with Contains()", []() {
        return !Contains(42, None<int>());
      });
      It("should return 0 when called with Length()", []() {
        return Length(None<int>()) == 0;
      });
      It("should return true when called with IsEmpty()", []() {
        return IsEmpty(None<int>());
      });
      It("should return true when called with Equals() and another none", []() {
        return Equals(None<int>(), None<int>());
      });
      It("should return false when called with Equals() and a Some()", []() {
        return !Equals(None<int>(), Some(42));
      });
      It("should return true when compared with == and another none", []() {
        return None<int>() == None<int>();
      });
      It("should return false when compared with == and a Some()", []() {
        return !(None<int>() == Some(42));
      });
      It("should return false when compared with != and another none", []() {
        return !(None<int>() != None<int>());
      });
      It("should return true when compared with != a Some()", []() {
        return None<int>() != Some(42);
      });
      It("should return a hash value of 0 when called with hashable()");
      It("should return none when called with Add() and another None()", []() {
        return Add(None<int>(), None<int>()) == None<int>();
      });
      It("should return Some(n) when called with Add() and a Some(n)", []() {
        return Add(None<int>(), Some(42)) == Some(42);
      });
      It("should return None() when called with Filter()", []() {
        return Filter(Equals(42), None<int>()) == None<int>();
      });
      It("should return LESS when passed through Compare() with Some()", []() {
        return Compare(None<int>(), Some(42)) == LESS;
      });
      It("should return EQUAL when passed through Compare() with another None()", []() {
        return Compare(None<int>(), None<int>()) == EQUAL;
      });
      It("should return None() when passed through Map()", []() {
        return Map(Multiply(2), None<int>()) == None<int>();
      });
      It("should return None() when passed through Alt() with another None()", []() {
        return Alt(None<int>(), None<int>()) == None<int>();
      });
      It("should return Some(n) when passed through Alt() with Some(n)", []() {
        return Alt(None<int>(), Some(42)) == Some(42);
      });
      It("should return None() when passed through || with another None()", []() {
        return (None<int>() || None<int>()) == None<int>();
      });
      It("should return Some(n) when passed through || with Some(n)", []() {
        return (None<int>() || Some(42)) == Some(42);
      });
      It("should return None() when called with FlatMap()", []() {
        return FlatMap([](auto n) { return Some(n * 2); }, None<int>()) == None<int>();
      });
      It("should return None() when called with Then() and another none", []() {
        return Then(None<int>(), None<int>()) == None<int>();
      });
      It("should return None() when called with Then() and a Some()", []() {
        return Then(None<int>(), Some(42)) == None<int>();
      });
      It("should return None() when called with MPlus() and another None()", []() {
        return MPlus(None<int>(), None<int>()) == None<int>();
      });
      It("should return Some(n) when called with MPlus() and another Some(n)", []() {
        return MPlus(None<int>(), Some(42)) == Some(42);
      });
      It("should return zero when called with Fold()", []() {
        return Fold(None<int>()) == 0;
      });
      It("should return zero when called with foldMap()", []() {
        return FoldMap(Identity<int>(), None<int>()) == 0;
      });
      It("should return init when called with FoldR()", []() {
        return FoldR(Add<int>(), 0, None<int>()) == 0;
      });
      It("should return init when called with FoldL()", []() {
        return FoldL(Add<int>(), 0, None<int>()) == 0;
      });
      It("should return the alternative when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, None<int>()) == 12;
      });
      It("should return the default when called with GetOrDefault()", []() {
        return GetOrDefault(42, None<int>()) == 42;
      });
      It("should return the string 'none' when called with Show()", []() {
        return Show(None<int>()) == std::string("None");
      });
    });
    Describe("in the case of type Some", []() {
      It("should return OPTION_SOME when calling get_type()", []() {
        return Some(42)->GetType() == OPTION_SOME;
      });
      It("should evalute the Some case when calling Match()", []() {
        return Match(Some(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
      });
      It("should return true when calling Contains() with a matching item", []() {
        return Contains(42, Some(42));
      });
      It("should return false when calling Contains() with a different item", []() {
        return !Contains(12, Some(42));
      });
      It("should return 1 when called with Length()", []() {
        return Length(Some(42)) == 1;
      });
      It("should return false when called with is_empty", []() {
        return !IsEmpty(Some(42));
      });
      It("should return false when called with Equals() and a none", []() {
        return IsEmpty(None<int>());
      });
      It("should return false when called with Equals() and a different item", []() {
        return !Equals(Some(42), None<int>());
      });
      It("should return true when called with Equals() and a matching item", []() {
        return Equals(Some(42), Some(42));
      });
      It("should return false when compared with == and a none", []() {
        return !(Some(42) == None<int>());
      });
      It("should return false when compared with == and a different item", []() {
        return !(Some(42) == Some(12));
      });
      It("should return true when compared with == with a matching item", []() {
        return Some(42) == Some(42);
      });
      It("should return true when compared with != and a none", []() {
        return Some(42) != None<int>();
      });
      It("should return true when compared with != and a different item", []() {
        return Some(42) != Some(12);
      });
      It("should return false when compared with != and a matching item", []() {
        return !(Some(42) != Some(42));
      });
      It("should return the hash of the inner item when called with hashable()");
      It("should return itself when called with Add() and a None()", []() {
        return Add(Some(42), None<int>()) == Some(42);
      });
      It("should return the sum of values when called with Add() and a value", []() {
        return Add(Some(42), Some(6)) == Some(48);
      });
      It("should return itself when called with + and a None()", []() {
        return (Some(42) + None<int>()) == Some(42);
      });
      It("should return the sum of values when called with + and a value", []() {
        return (Some(42) + Some(6)) == Some(48);
      });
      It("should return None() when called with Filter() and a non match predicate", []() {
        return Filter(Equals(12), Some(42)) == None<int>();
      });
      It("should return itself when called with Filter() and a matching predicate", []() {
        return Filter(Equals(42), Some(42)) == Some(42);
      });
      It("should return GREATER when called with Compare() and a None()", []() {
        return Compare(Some(42), None<int>()) == GREATER;
      });
      It("should return GREATER when called with Compare() and a lesser Some()", []() {
        return Compare(Some(42), Some(8)) == GREATER;
      });
      It("should return EQUAL when called with Compare() and an equal Some()", []() {
        return Compare(Some(42), Some(42)) == EQUAL;
      });
      It("should return LESS when called with Compare() and a greater Some()", []() {
        return Compare(Some(42), Some(100)) == LESS;
      });
      It("should return n * 2 when called with Map(*2)", []() {
        return Map(Multiply(2), Some(42)) == Some(84);
      });
      It("should return itself when called with Alt() and another Some()", []() {
        return Alt(Some(42), Some(12)) == Some(42);
      });
      It("should return itself when called with Alt() and a None()", []() {
        return Alt(Some(42), None<int>()) == Some(42);
      });
      It("should return itself when compared with || and another Some()", []() {
        return (Some(42) || Some(12)) == Some(42);
      });
      It("should return itself when compared with || and None()", []() {
        return (Some(42) || None<int>()) == Some(42);
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        return FlatMap([](auto n) { return None<int>(); }, Some(42)) == None<int>();
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        return FlatMap([](auto n) { return Some(n * 2); }, Some(42)) == Some(84);
      });
      It("should return the next Some(n) when called with Then()", []() {
        return Then(Some(12), Some(42)) == Some(42);
      });
      It("should return None() when called with Then() and a None()", []() {
        return Then(Some(42), None<int>()) == None<int>();
      });
      It("should return the inner value when called with Fold()", []() {
        return Fold(Some(42)) == 42;
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        return FoldMap(Identity<int>(), Some(42)) == 42;
      });
      It("should return the folded value when called with FoldR()", []() {
        return FoldR(Add<int>(), 12, Some(42)) == 54;
      });
      It("should return the folded value when called with FoldL()", []() {
        return FoldL(Add<int>(), 12, Some(42)) == 54;
      });
      It("should return the inner value when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, Some(42)) == 42;
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        return GetOrDefault(12, Some(42)) == 42;
      });
      It("should return the string 'Some(n)' when called with Show()", []() {
        return Show(Some(42)) == std::string("Some(42)");
      });
    });
  });
}

}

#endif
