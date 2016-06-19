#pragma once

#include <everest/test/bdd.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

void MutableMapSpecification() {
  Describe("A MutableMap type", []() {
    /*
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(MutableSet<int>({1, 2, 3}), MutableSet<int>({4, 5, 6}));
      auto failure = "Equals(MutableSet(1, 2, 3), MutableSet(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(MutableSet<int>({1, 2, 3}), MutableSet<int>({1, 2, 3}));
      auto failure = "Equals(MutableSet(1, 2, 3), MutableSet(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(MutableSet<int>({1, 2, 3}), MutableSet<int>({1, 2}));
      auto failure = "Equals(MutableSet(1, 2, 3), MutableSet(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = MutableSet<int>({1, 2, 3}) == MutableSet<int>({4, 5, 6});
      auto failure = "MutableSet(1, 2, 3) == MutableSet(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = MutableSet<int>({1, 2, 3}) == MutableSet<int>({1, 2, 3});
      auto failure = "MutableSet(1, 2, 3) == MutableSet(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = MutableSet<int>({1, 2, 3}) == MutableSet<int>({4, 5});
      auto failure = "MutableSet(1, 2, 3) === MutableSet(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = MutableSet<int>({1, 2, 3}) != MutableSet<int>({4, 5, 6});
      auto failure = "MutableSet(1, 2, 3) != MutableSet(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = MutableSet<int>({1, 2, 3}) != MutableSet<int>({1, 2, 3});
      auto failure = "MutableSet(1, 2, 3) != MutableSet(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = MutableSet<int>({1, 2, 3}) != MutableSet<int>({4, 5});
      auto failure = "MutableSet(1, 2, 3) != MutableSet(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return the mapped MutableSet when called with Map(Add(2))", [](){
      auto expected = MutableSet<int>({2, 4, 6});
      auto result   = Map(Multiply(2), MutableSet<int>({1, 2, 3}));
      auto failure  = "Map(Multiply(2), MutableSet(1, 2, 3)) did not return MutableSet(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, MutableSet<int>({1, 2, 3}));
      auto failure = "Contains(1, MutableSet(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, MutableSet<int>({1, 2, 3}));
      auto failure = "Contains(6, MutableSet(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an MutableSet w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(MutableSet<int>({1, 2, 3}));
      auto failure  = "Length(MutableSet(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty MutableSet", []() {
      auto result  = IsEmpty(MutableSet<int>({1, 2, 3}));
      auto failure = "IsEmpty(MutableSet(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty MutableSet", []() {
      auto result  = IsEmpty(MutableSet<int>({}));
      auto failure = "IsEmpty(MutableSet()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged MutableSet when calling Add() w/ two arrays", []() {
      auto expected = MutableSet<int>({1, 2, 3, 4, 5});
      auto result   = Add(MutableSet<int>({1, 2, 3}), MutableSet<int>({4, 5}));
      auto failure  = "Add(MutableSet(1, 2, 3), MutableSet(4, 5)) did not return MutableSet(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty MutableSet when calling Zero()", []() {
      auto expected = MutableSet<int>({});
      auto result   = Zero<MutableSet<int>>();
      auto failure  = "Zero<MutableSet<int, 0>>() did not return MutableSet()";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for a null vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableSet<int>());
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for an empty vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableSet<int>(32));
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 3 for a vector with three elements", []() {
      auto subject = MutableSet<int>({1, 2, 3});
      size_t expected = 3;
      auto result     = Length(subject);
      auto failure    = "The vector returned the incorrect length";
      AssertEquals(failure, expected, result);
    });
    Describe("of [1,2,3,4] called with FilterInPlace(n % 2 == 0)", []() {
      auto subject = MutableSet<int>({1, 2, 3, 4});
      FilterInPlace([](auto n) { return n % 2 == 0; }, subject);
      It("Should be of length 2", [&]() {
        AssertEquals((size_t)2, Length(subject));
      });
      It("Should return 2 for the first element", [&]() {
        AssertTrue(Contains(2, subject));
      });
      It("Should return 4 for the second element", [&]() {
        AssertTrue(Contains(4, subject));
      });
    });
     */
    Describe("of value {'one': 1, 'two': 2, 'three': 3, 'four': 4}", []() {
      auto subject = MutableMap<String, int>();
      PutInPlace(String("one"), 1, subject);
      PutInPlace(String("two"), 2, subject);
      PutInPlace(String("three"), 3, subject);
      PutInPlace(String("four"), 4, subject);
      It("Should render the correct string when called with Shows()", [&](){
        auto expected = String("MutableMap(three: 3, four: 4, two: 2, one: 1)");
        auto result   = Show(subject);
        PrintLn(result);
        AssertEquals(expected, result);
      });
      It("Should return false when called with Contains('zero')", [&]() {
        AssertFalse(Contains(String("zero"), subject));
      });
      It("Should return true when called with Contains('one')", [&]() {
        AssertTrue(Contains(String("one"), subject));
      });
      It("Should return true when called with Contains('two')", [&]() {
        AssertTrue(Contains(String("two"), subject));
      });
      It("Should return true when called with Contains('three')", [&]() {
        AssertTrue(Contains(String("three"), subject));
      });
      It("Should return true when called with Contains('four')", [&]() {
        AssertTrue(Contains(String("four"), subject));
      });
      It("Should return false when called with Contains('five')", [&]() {
        AssertFalse(Contains(String("five"), subject));
      });
      It("Should return nullptr when called with Get('zero')", [&]() {
        AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject));
      });
      It("Should return 1 when called with Get('one')", [&]() {
        AssertEquals(1, *GetInPlace(String("one"), subject));
      });
      It("Should return 2 when called with Get('two')", [&]() {
        AssertEquals(2, *GetInPlace(String("two"), subject));
      });
      It("Should return 3 when called with Get('three')", [&]() {
        AssertEquals(3, *GetInPlace(String("three"), subject));
      });
      It("Should return 4 when called with Get('four')", [&]() {
        AssertEquals(4, *GetInPlace(String("four"), subject));
      });
      It("Should return nullptr when called with Get('five')", [&]() {
        AssertEquals<int>(nullptr, GetInPlace(String("five"), subject));
      });
      Describe("and we call Remove(1)", [&]() {
        RemoveInPlace(String("one"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertTrue(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject));
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject));
        });
        It("Should return 2 when called with Get('two')", [&]() {
          AssertEquals(2, *GetInPlace(String("two"), subject));
        });
        It("Should return 3 when called with Get('three')", [&]() {
          AssertEquals(3, *GetInPlace(String("three"), subject));
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, *GetInPlace(String("four"), subject));
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject));
        });
      });
      Describe("and we call Remove(2)", [&]() {
        RemoveInPlace(String("two"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject));
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject));
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject));
        });
        It("Should return 3 when called with Get('three')", [&]() {
          AssertEquals(3, *GetInPlace(String("three"), subject));
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, *GetInPlace(String("four"), subject));
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject));
        });
      });
      Describe("and we call Remove(3)", [&]() {
        RemoveInPlace(String("three"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertFalse(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject));
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject));
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject));
        });
        It("Should return nullptr when called with Get('three')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("three"), subject));
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, *GetInPlace(String("four"), subject));
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject));
        });
      });
      Describe("and we call Remove(4)", [&]() {
        RemoveInPlace(String("four"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertFalse(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertFalse(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject));
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject));
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject));
        });
        It("Should return nullptr when called with Get('three')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("three"), subject));
        });
        It("Should return nullptr when called with Get('four')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("four"), subject));
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject));
        });
      });
    });
  });
}

}