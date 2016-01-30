#ifndef TRAITOROUS_LOCAL_OPTION_SPEC_H
#define TRAITOROUS_LOCAL_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/local_option.h"
#include "functions/identity.h"

namespace traitorous {

void LocalOptionSpecification() {
  describe("A local_option type", []() {
    it("should have a zero value of nOne()", []() {
      return Zero<LocalOption<int>>() == LocalNone<int>();
    });
    describe("in the case of type none", []() {
      it("should return OPTION_NONE when calling get_type()", []() {
        return LocalNone<int>().get_type() == OPTION_NONE;
      });
      it("should evalute the none case when calling Match()", []() {
        return Match(LocalNone<int>(),
                     []()       { return true; },
                     [](auto n) { return false; }
        );
      });
      it("should return false when called with Contains()", []() {
        return !Contains(42, LocalNone<int>());
      });
      it("should return 0 when called with Length()", []() {
        return Length(LocalNone<int>()) == 0;
      });
      it("should return true when called with IsEmpty()", []() {
        return IsEmpty(LocalNone<int>());
      });
      it("should return true when called with Equals() and another none", []() {
        return Equals(LocalNone<int>(), LocalNone<int>());
      });
      it("should return false when called with Equals() and a LocalSome()", []() {
        return !Equals(LocalNone<int>(), LocalSome(42));
      });
      it("should return true when compared with == and another none", []() {
        return LocalNone<int>() == LocalNone<int>();
      });
      it("should return false when compared with == and a LocalSome()", []() {
        return !(LocalNone<int>() == LocalSome(42));
      });
      it("should return false when compared with != and another none", []() {
        return !(LocalNone<int>() != LocalNone<int>());
      });
      it("should return true when compared with != a LocalSome()", []() {
        return LocalNone<int>() != LocalSome(42);
      });
      it("should return a hash value of 0 when called with hashable()");
      it("should return none when called with Add() and another nOne()", []() {
        return Add(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return LocalSome(n) when called with Add() and a LocalSome(n)", []() {
        return Add(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      it("should return nOne() when called with Filter()", []() {
        return Filter(Equals(42), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return LESS when passed through Compare() with LocalSome()", []() {
        return Compare(LocalNone<int>(), LocalSome(42)) == LESS;
      });
      it("should return EQUAL when passed through Compare() with another nOne()", []() {
        return Compare(LocalNone<int>(), LocalNone<int>()) == EQUAL;
      });
      it("should return nOne() when passed through Map()", []() {
        return Map(Multiply(2), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return nOne() when passed through Alt() with another nOne()", []() {
        return Alt(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return LocalSome(n) when passed through Alt() with LocalSome(n)", []() {
        return Alt(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      it("should return nOne() when passed through || with another nOne()", []() {
        return (LocalNone<int>() || LocalNone<int>()) == LocalNone<int>();
      });
      it("should return LocalSome(n) when passed through || with LocalSome(n)", []() {
        return (LocalNone<int>() || LocalSome(42)) == LocalSome(42);
      });
      it("should return nOne() when called with FlatMap()", []() {
        return FlatMap([](auto n) { return LocalSome(n * 2); }, LocalNone<int>()) == LocalNone<int>();
      });
      it("should return nOne() when called with Then() and another none", []() {
        return Then(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return nOne() when called with Then() and a LocalSome()", []() {
        return Then(LocalNone<int>(), LocalSome(42)) == LocalNone<int>();
      });
      it("should return nOne() when called with MPlus() and another nOne()", []() {
        return MPlus(LocalNone<int>(), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return LocalSome(n) when called with MPlus() and another LocalSome(n)", []() {
        return MPlus(LocalNone<int>(), LocalSome(42)) == LocalSome(42);
      });
      it("should return zero when called with Fold()", []() {
        return Fold(LocalNone<int>()) == 0;
      });
      it("should return zero when called with foldMap()", []() {
        return FoldMap(Identity<int>(), LocalNone<int>()) == 0;
      });
      it("should return init when called with FoldR()", []() {
        return FoldR(Add<int>(), 0, LocalNone<int>()) == 0;
      });
      it("should return init when called with FoldL()", []() {
        return FoldL(Add<int>(), 0, LocalNone<int>()) == 0;
      });
      it("should return the alternative when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalNone<int>()) == 12;
      });
      it("should return the default when called with GetOrDefault()", []() {
        return GetOrDefault(42, LocalNone<int>()) == 42;
      });
      it("should return the string 'none' when called with Show()", []() {
        return Show(LocalNone<int>()) == std::string("none");
      });
    });
    describe("in the case of type LocalSome", []() {
      it("should return OPTION_SOME when calling get_type()", []() {
        return LocalSome(42).get_type() == OPTION_SOME;
      });
      it("should evalute the LocalSome case when calling Match()", []() {
        return Match(LocalSome(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
      });
      it("should return true when calling Contains() with a matching item", []() {
        return Contains(42, LocalSome(42));
      });
      it("should return false when calling Contains() with a different item", []() {
        return !Contains(12, LocalSome(42));
      });
      it("should return 1 when called with Length()", []() {
        return Length(LocalSome(42)) == 1;
      });
      it("should return false when called with is_empty", []() {
        return !IsEmpty(LocalSome(42));
      });
      it("should return false when called with Equals() and a none", []() {
        return IsEmpty(LocalNone<int>());
      });
      it("should return false when called with Equals() and a different item", []() {
        return !Equals(LocalSome(42), LocalNone<int>());
      });
      it("should return true when called with Equals() and a matching item", []() {
        return Equals(LocalSome(42), LocalSome(42));
      });
      it("should return false when compared with == and a none", []() {
        return !(LocalSome(42) == LocalNone<int>());
      });
      it("should return false when compared with == and a different item", []() {
        return !(LocalSome(42) == LocalSome(12));
      });
      it("should return true when compared with == with a matching item", []() {
        return LocalSome(42) == LocalSome(42);
      });
      it("should return true when compared with != and a none", []() {
        return LocalSome(42) != LocalNone<int>();
      });
      it("should return true when compared with != and a different item", []() {
        return LocalSome(42) != LocalSome(12);
      });
      it("should return false when compared with != and a matching item", []() {
        return !(LocalSome(42) != LocalSome(42));
      });
      it("should return the hash of the inner item when called with hashable()");
      it("should return itself when called with Add() and a nOne()", []() {
        return Add(LocalSome(42), LocalNone<int>()) == LocalSome(42);
      });
      it("should return the sum of values when called with Add() and a value", []() {
        return Add(LocalSome(42), LocalSome(6)) == LocalSome(48);
      });
      it("should return itself when called with + and a nOne()", []() {
        return (LocalSome(42) + LocalNone<int>()) == LocalSome(42);
      });
      it("should return the sum of values when called with + and a value", []() {
        return (LocalSome(42) + LocalSome(6)) == LocalSome(48);
      });
      it("should return nOne() when called with Filter() and a non match predicate", []() {
        return Filter(Equals(12), LocalSome(42)) == LocalNone<int>();
      });
      it("should return itself when called with Filter() and a matching predicate", []() {
        return Filter(Equals(42), LocalSome(42)) == LocalSome(42);
      });
      it("should return GREATER when called with Compare() and a nOne()", []() {
        return Compare(LocalSome(42), LocalNone<int>()) == GREATER;
      });
      it("should return GREATER when called with Compare() and a lesser LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(8)) == GREATER;
      });
      it("should return EQUAL when called with Compare() and an equal LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(42)) == EQUAL;
      });
      it("should return LESS when called with Compare() and a greater LocalSome()", []() {
        return Compare(LocalSome(42), LocalSome(100)) == LESS;
      });
      it("should return n * 2 when called with Map(*2)", []() {
        return Map(Multiply(2), LocalSome(42)) == LocalSome(84);
      });
      it("should return itself when called with Alt() and another LocalSome()", []() {
        return Alt(LocalSome(42), LocalSome(12)) == LocalSome(42);
      });
      it("should return itself when called with Alt() and a nOne()", []() {
        return Alt(LocalSome(42), LocalNone<int>()) == LocalSome(42);
      });
      it("should return itself when compared with || and another LocalSome()", []() {
        return (LocalSome(42) || LocalSome(12)) == LocalSome(42);
      });
      it("should return itself when compared with || and nOne()", []() {
        return (LocalSome(42) || LocalNone<int>()) == LocalSome(42);
      });
      it("should return none when called with FlatMap() and a function -> none", []() {
        return FlatMap([](auto n) { return LocalNone<int>(); }, LocalSome(42)) == LocalNone<int>();
      });
      it("should return n * 2 when called with flat_map and a function -> *2", []() {
        return FlatMap([](auto n) { return LocalSome(n * 2); }, LocalSome(42)) == LocalSome(84);
      });
      it("should return the next LocalSome(n) when called with Then()", []() {
        return Then(LocalSome(12), LocalSome(42)) == LocalSome(42);
      });
      it("should return nOne() when called with Then() and a nOne()", []() {
        return Then(LocalSome(42), LocalNone<int>()) == LocalNone<int>();
      });
      it("should return the inner value when called with Fold()", []() {
        return Fold(LocalSome(42)) == 42;
      });
      it("should return the inner value mapped when called with FoldMap()", []() {
        return FoldMap(Identity<int>(), LocalSome(42)) == 42;
      });
      it("should return the folded value when called with FoldR()", []() {
        return FoldR(Add<int>(), 12, LocalSome(42)) == 54;
      });
      it("should return the folded value when called with FoldL()", []() {
        return FoldL(Add<int>(), 12, LocalSome(42)) == 54;
      });
      it("should return the inner value when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalSome(42)) == 42;
      });
      it("should return the inner value when called with GetOrDefault()", []() {
        return GetOrDefault(12, LocalSome(42)) == 42;
      });
      it("should return the string 'LocalSome(n)' when called with Show()", []() {
        return Show(LocalSome(42)) == std::string("LocalSome(42)");
      });
    });
  });
}

}

#endif
