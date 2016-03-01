#ifndef TRAITOROUS_LOCAL_CHECKED_SPEC_H
#define TRAITOROUS_LOCAL_CHECKED_SPEC_H

#include "test/bdd.h"

#include "functions/identity.h"

#include "containers/checked.h"

namespace traitorous {

void LocalCheckedSpecification() {
  Describe("A LocalChecked type", []() {
    It("should have a zero value of None()", []() {
      return Zero<LocalChecked<bool, int>>() == LocalOk<bool, int>(0);
    });
    Describe("in the case of type LocalOk", []() {
      It("should return OK when calling GetType()", []() {
        return LocalOk<bool, int>(42).GetType() == CheckedType::OK;
      });
      It("should evalute the ok case when calling Match()", []() {
        return Match(LocalOk<bool, int>(42),
          [](const bool& error) { return false; },
          [](const int& ok)     { return true; }
        );
      });
      It("should return true w hen calling Contains() with a matching item", []() {
        return Contains(42, LocalOk<bool, int>(42));
      });
      It("should return false when calling Contains() with a different item", []() {
        return !Contains(12, LocalOk<bool, int>(42));
      });
      It("should return 1 when called with Length()", []() {
        return Length(LocalOk<bool, int>(42)) == 1;
      });
      It("should return false when called with is_empty", []() {
        return !IsEmpty(LocalOk<bool, int>(42));
      });
      It("should return false when called with Equals() and a different item", []() {
        return !Equals(LocalOk<bool, int>(42), LocalError<bool, int>(false));
      });
      It("should return true when called with Equals() and a matching item", []() {
        return Equals(LocalOk<bool, int>(42), LocalOk<bool, int>(42));
      });
      It("should return false when compared with == and a none", []() {
        return !(LocalOk<bool, int>(42) == LocalError<bool, int>(false));
      });
      It("should return false when compared with == and a different item", []() {
        return !(LocalOk<bool, int>(42) == LocalOk<bool, int>(12));
      });
      It("should return true when compared with == with a matching item", []() {
        return LocalOk<bool, int>(42) == LocalOk<bool, int>(42);
      });
      It("should return true when compared with != and a none", []() {
        return LocalOk<bool, int>(42) != LocalError<bool, int>(false);
      });
      It("should return true when compared with != and a different item", []() {
        return LocalOk<bool, int>(42) != LocalOk<bool, int>(12);
      });
      It("should return false when compared with != and a matching item", []() {
        return !(LocalOk<bool, int>(42) != LocalOk<bool, int>(42));
      });
      It("should return the hash of the inner item when called with hashable()", []() {
        return Hash(LocalOk<bool, int>(42)) == Hash(42);
      });
      It("should return the error when called with Add() and an error", []() {
        return Add(LocalOk<bool, int>(42), LocalError<bool, int>(false)) == LocalError<bool, int>(false);
      });
      It("should return the sum of values when called with Add() and a value", []() {
        return Add(LocalOk<bool, int>(42), LocalOk<bool, int>(6)) == LocalOk<bool, int>(48);
      });
      It("should return the error when called with + and an error", []() {
        return (LocalOk<bool, int>(42) + LocalError<bool, int>(false)) == LocalError<bool, int>(false);
      });
      It("should return the sum of values when called with + and a value", []() {
        return (LocalOk<bool, int>(42) + LocalOk<bool, int>(6)) == LocalOk<bool, int>(48);
      });
      It("should return GREATER when called with Compare() and an error", []() {
        return Compare(LocalOk<bool, int>(42), LocalError<bool, int>(false)) == GREATER;
      });
      It("should return GREATER when called with Compare() and a lesser LocalOk()", []() {
        return Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(8)) == GREATER;
      });
      It("should return EQUAL when called with Compare() and an equal LocalOk()", []() {
        return Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(42)) == EQUAL;
      });
      It("should return LESS when called with Compare() and a greater LocalOk()", []() {
        return Compare(LocalOk<bool, int>(42), LocalOk<bool, int>(100)) == LESS;
      });
      It("should return n * 2 when called with Map(*2)", []() {
        return Map(Multiply(2), LocalOk<bool, int>(42)) == LocalOk<bool, int>(84);
      });
      It("should return itself when called with Alt() and another LocalOk()", []() {
        return Alt(LocalOk<bool, int>(42), LocalOk<bool, int>(12)) == LocalOk<bool, int>(42);
      });
      It("should return itself when called with Alt() and a LocalError()", []() {
        return Alt(LocalOk<bool, int>(42), LocalError<bool, int>(false)) == LocalOk<bool, int>(42);
      });
      It("should return itself when compared with || and another LocalOk()", []() {
        return (LocalOk<bool, int>(42) || LocalOk<bool, int>(12)) == LocalOk<bool, int>(42);
      });
      It("should return itself when compared with || and LocalError()", []() {
        return (LocalOk<bool, int>(42) || LocalError<bool, int>(false)) == LocalOk<bool, int>(42);
      });
      It("should return none when called with FlatMap() and a function -> none", []() {
        return FlatMap([](auto n) { return LocalError<bool, int>(false); }, LocalOk<bool, int>(42)) == LocalError<bool, int>(false);
      });
      It("should return n * 2 when called with flat_map and a function -> *2", []() {
        return FlatMap([](auto n) { return LocalOk<bool, int>(n * 2); }, LocalOk<bool, int>(42)) == LocalOk<bool, int>(84);
      });
      It("should return the next LocalOk(n) when called with Then()", []() {
        return Then(LocalOk<bool, int>(12), LocalOk<bool, int>(42)) == LocalOk<bool, int>(42);
      });
      It("should return the error when called with Then() and an error", []() {
        return Then(LocalOk<bool, int>(42), LocalError<bool, int>(false)) == LocalError<bool, int>(false);
      });
      It("should return the inner value when called with Fold()", []() {
        return Fold(LocalOk<bool, int>(42)) == 42;
      });
      It("should return the inner value mapped when called with FoldMap()", []() {
        return FoldMap(Identity<int>(), LocalOk<bool, int>(42)) == 42;
      });
      It("should return the folded value when called with FoldR()", []() {
        return FoldR(Add<int>(), 12, LocalOk<bool, int>(42)) == 54;
      });
      It("should return the folded value when called with FoldL()", []() {
        return FoldL(Add<int>(), 12, LocalOk<bool, int>(42)) == 54;
      });
      It("should return the inner value when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalOk<bool, int>(42)) == 42;
      });
      It("should return the inner value when called with GetOrDefault()", []() {
        return GetOrDefault(12, LocalOk<bool, int>(42)) == 42;
      });
      It("should return the string 'LocalOk(n)' when called with Show()", []() {
        return Show(LocalOk<bool, int>(42)) == std::string("LocalOk(42)");
      });
    });
    Describe("in the case of type LocalError", []() {
      It("should return ERROR when calling GetType()", []() {
        return LocalError<bool, int>(false).GetType() == CheckedType::ERROR;
      });
      It("should evalute the none case when calling Match()", []() {
        return Match(LocalError<bool, int>(false),
          [](auto error) { return true; },
          [](auto ok)    { return false; }
        );
      });
      It("should return false when called with Contains()", []() {
        return !Contains(42, LocalError<bool, int>(false));
      });
      It("should return 0 when called with Length()", []() {
        return Length(LocalError<bool, int>(false)) == 0;
      });
      It("should return true when called with IsEmpty()", []() {
        return IsEmpty(LocalError<bool, int>(false));
      });
      It("should return true when called with Equals() and a matching error", []() {
        return Equals(LocalError<bool, int>(false), LocalError<bool, int>(false));
      });
      It("should return false when called with Equals() and a LocalOk()", []() {
        return !Equals(LocalError<bool, int>(false), LocalOk<bool, int>(42));
      });
      It("should return true when compared with == a matching error", []() {
        return LocalError<bool, int>(false) == LocalError<bool, int>(false);
      });
      It("should return false when compared with == and a LocalOk()", []() {
        return !(LocalError<bool, int>(false) == LocalOk<bool, int>(42));
      });
      It("should return false when compared with != and a matching error", []() {
        return !(LocalError<bool, int>(false) != LocalError<bool, int>(false));
      });
      It("should return true when compared with != a LocalOk()", []() {
        return LocalError<bool, int>(false) != LocalOk<bool, int>(42);
      });
      It("should return a hash value of 0 when called with hashable()", []() {
        return Hash(LocalError<bool, int>(false)) == 0;
      });
      It("should return itself when called with Add() and another LocalError()", []() {
        return Add(LocalError<bool, int>(false), LocalError<bool, int>(true)) == LocalError<bool, int>(false);
      });
      It("should return itself when called with Add() and a LocalOk(n)", []() {
        return Add(LocalError<bool, int>(false), LocalOk<bool, int>(42)) == LocalError<bool, int>(false);
      });
      It("should return LESS when passed through Compare() with LocalOk()", []() {
        return Compare(LocalError<bool, int>(false), LocalOk<bool, int>(42)) == LESS;
      });
      It("should return EQUAL when passed through Compare() with a matching LocalError()", []() {
        return Compare(LocalError<bool, int>(false), LocalError<bool, int>(false)) == EQUAL;
      });
      It("should return itself when passed through Map()", []() {
        return Map(Multiply(2), LocalError<bool, int>(false)) == LocalError<bool, int>(false);
      });
      It("should return the other error when passed through Alt() with another error", []() {
        return Alt(LocalError<bool, int>(false), LocalError<bool, int>(true)) == LocalError<bool, int>(true);
      });
      It("should return the ok when passed through Alt() with LocalOk(n)", []() {
        return Alt(LocalError<bool, int>(false), LocalOk<bool, int>(42)) == LocalOk<bool, int>(42);
      });
      It("should return the other error when passed through || with another LocalError()", []() {
        return (LocalError<bool, int>(false) || LocalError<bool, int>(true)) == LocalError<bool, int>(true);
      });
      It("should return LocalOk(n) when passed through || with LocalOk(n)", []() {
        return (LocalError<bool, int>(false) || LocalOk<bool, int>(42)) == LocalOk<bool, int>(42);
      });
      It("should return itself when called with FlatMap()", []() {
        return FlatMap([](auto n) { return LocalOk<bool, int>(n * 2); }, LocalError<bool, int>(false)) == LocalError<bool, int>(false);
      });
      It("should return the first error when called with Then() and another error", []() {
        return Then(LocalError<bool, int>(false), LocalError<bool, int>(true)) == LocalError<bool, int>(false);
      });
      It("should return itself when called with Then() and a LocalOk()", []() {
        return Then(LocalError<bool, int>(false), LocalOk<bool, int>(42)) == LocalError<bool, int>(false);
      });
      It("should return zero when called with Fold()", []() {
        return Fold(LocalError<bool, int>(false)) == 0;
      });
      It("should return zero when called with foldMap()", []() {
        return FoldMap(Identity<int>(), LocalError<bool, int>(false)) == 0;
      });
      It("should return init when called with FoldR()", []() {
        return FoldR(Add<int>(), 0, LocalError<bool, int>(false)) == 0;
      });
      It("should return init when called with FoldL()", []() {
        return FoldL(Add<int>(), 0, LocalError<bool, int>(false)) == 0;
      });
      It("should return the alternative when called with GetOrElse()", []() {
        return GetOrElse([]() { return 12; }, LocalError<bool, int>(false)) == 12;
      });
      It("should return the default when called with GetOrDefault()", []() {
        return GetOrDefault(42, LocalError<bool, int>(false)) == 42;
      });
      It("should return the correct string when called with Show()", []() {
        return Show(LocalError<bool, int>(false)) == std::string("LocalError(false)");
      });
    });
  });
}

}

#endif
