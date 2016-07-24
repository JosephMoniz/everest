#pragma once

#include <everest/test/bdd.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>
#include <everest/containers/mutable/mutable_sorted_vector_set.h>

namespace everest {

void MutableSortedVectorSetSpecification() {
  Describe("A MutableSortedVectorSet type", []() {
    Describe("That contains {1, 2, 3, 4}", []() {
      auto set = MutableSortedVectorSet<int>({3, 4, 1, 2});
      It("Should be ordered", [&]() {
        auto pointer = Pointer(set);
        AssertEquals(1, pointer[0]);
        AssertEquals(2, pointer[1]);
        AssertEquals(3, pointer[2]);
        AssertEquals(4, pointer[3]);
      });
      It("Should return false when calling with Contains(0)", [&]() {
        AssertFalse(set.Contains(0));
      });
      It("Should return true when calling with Contains(1)", [&]() {
        AssertTrue(set.Contains(1));
      });
      It("Should return true when calling with Contains(2)", [&]() {
        AssertTrue(set.Contains(2));
      });
      It("Should return true when calling with Contains(3)", [&]() {
        AssertTrue(set.Contains(3));
      });
      It("Should return true when calling with Contains(4)", [&]() {
        AssertTrue(set.Contains(4));
      });
      It("Should return false when calling with Contains(5)", [&]() {
        AssertFalse(set.Contains(5));
      });
    });
    Describe("That contains {1, 2, 3, 4, 5}", []() {
      auto set = MutableSortedVectorSet<int>({3, 5, 1, 2, 4});
      It("Should be ordered", [&]() {
        auto pointer = Pointer(set);
        AssertEquals(1, pointer[0]);
        AssertEquals(2, pointer[1]);
        AssertEquals(3, pointer[2]);
        AssertEquals(4, pointer[3]);
        AssertEquals(5, pointer[4]);
      });
      It("Should return false when calling with Contains(0)", [&]() {
        AssertFalse(set.Contains(0));
      });
      It("Should return true when calling with Contains(1)", [&]() {
        AssertTrue(set.Contains(1));
      });
      It("Should return true when calling with Contains(2)", [&]() {
        AssertTrue(set.Contains(2));
      });
      It("Should return true when calling with Contains(3)", [&]() {
        AssertTrue(set.Contains(3));
      });
      It("Should return true when calling with Contains(4)", [&]() {
        AssertTrue(set.Contains(4));
      });
      It("Should return true when calling with Contains(5)", [&]() {
        AssertTrue(set.Contains(5));
      });
      It("Should return false when calling with Contains(6)", [&]() {
        AssertFalse(set.Contains(6));
      });
    });
    It("Should render the correct string when called with Shows()", [](){
      auto expected = String("MutableSortedVectorSet(1, 2, 3)");
      auto result   = Show(MutableSortedVectorSet<int>({2, 3, 1}));
      AssertEquals(expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(MutableSortedVectorSet<int>({1, 2, 3}), MutableSortedVectorSet<int>({4, 5, 6}));
      auto failure = "Equals(MutableSet(1, 2, 3), MutableSet(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(MutableSortedVectorSet<int>({1, 2, 3}), MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure = "Equals(MutableSortedVectorSet(1, 2, 3), MutableSortedVectorSet(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(MutableSortedVectorSet<int>({1, 2, 3}), MutableSortedVectorSet<int>({1, 2}));
      auto failure = "Equals(MutableSortedVectorSet(1, 2, 3), MutableSortedVectorSet(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) == MutableSortedVectorSet<int>({4, 5, 6});
      auto failure = "MutableSortedVectorSet(1, 2, 3) == MutableSortedVectorSet(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) == MutableSortedVectorSet<int>({1, 2, 3});
      auto failure = "MutableSortedVectorSet(1, 2, 3) == MutableSortedVectorSet(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) == MutableSortedVectorSet<int>({4, 5});
      auto failure = "MutableSortedVectorSet(1, 2, 3) === MutableSortedVectorSet(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) != MutableSortedVectorSet<int>({4, 5, 6});
      auto failure = "MutableSortedVectorSet(1, 2, 3) != MutableSortedVectorSet(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) != MutableSortedVectorSet<int>({1, 2, 3});
      auto failure = "MutableSortedVectorSet(1, 2, 3) != MutableSortedVectorSet(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = MutableSortedVectorSet<int>({1, 2, 3}) != MutableSortedVectorSet<int>({4, 5});
      auto failure = "MutableSortedVectorSet(1, 2, 3) != MutableSortedVectorSet(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return the mapped MutableSortedVectorSet when called with Map(Add(2))", [](){
      auto expected = MutableSortedVectorSet<int>({2, 4, 6});
      auto result   = Map(Multiply(2), MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure  = "Map(Multiply(2), MutableSortedVectorSet(1, 2, 3)) did not return MutableSortedVectorSet(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure = "Contains(1, MutableSortedVectorSet(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure = "Contains(6, MutableSortedVectorSet(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an MutableSortedVectorSet w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure  = "Length(MutableSortedVectorSet(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty MutableSortedVectorSet", []() {
      auto result  = IsEmpty(MutableSortedVectorSet<int>({1, 2, 3}));
      auto failure = "IsEmpty(MutableSortedVectorSet(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty MutableSortedVectorSet", []() {
      auto result  = IsEmpty(MutableSortedVectorSet<int>({}));
      auto failure = "IsEmpty(MutableSortedVectorSet()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged MutableSet when calling Add() w/ two arrays", []() {
      auto expected = MutableSortedVectorSet<int>({1, 2, 3, 4, 5});
      auto result   = Add(MutableSortedVectorSet<int>({1, 4, 3}), MutableSortedVectorSet<int>({5, 2}));
      auto failure  = "Add(MutableSet(1, 2, 3), MutableSet(4, 5)) did not return MutableSet(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty MutableSet when calling Zero()", []() {
      auto expected = MutableSortedVectorSet<int>({});
      auto result   = Zero<MutableSortedVectorSet<int>>();
      auto failure  = "Zero<MutableSet<int, 0>>() did not return MutableSet()";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for a null vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableSortedVectorSet<int>());
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for an empty vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableSortedVectorSet<int>());
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 3 for a vector with three elements", []() {
      auto subject    = MutableSortedVectorSet<int>({1, 2, 3});
      size_t expected = 3;
      auto result     = Length(subject);
      auto failure    = "The vector returned the incorrect length";
      AssertEquals(failure, expected, result);
    });
    Describe("of [1,2,3,4] called with FilterInPlace(n % 2 == 0)", []() {
      auto subject = MutableSortedVectorSet<int>({1, 2, 3, 4});
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
    Describe("of value {1, 2, 3, 4}", []() {
      auto subject = MutableSortedVectorSet<int>({1, 2, 3, 4});
      It("Should return a length of 4", [&]() {
        AssertEquals((size_t)4, Length(subject));
      });
      It("Should return false when called with Contains(0)", [&]() {
        AssertFalse(Contains(0, subject));
      });
      It("Should return true when called with Contains(1)", [&]() {
        AssertTrue(Contains(1, subject));
      });
      It("Should return true when called with Contains(2)", [&]() {
        AssertTrue(Contains(2, subject));
      });
      It("Should return true when called with Contains(3)", [&]() {
        AssertTrue(Contains(3, subject));
      });
      It("Should return true when called with Contains(4)", [&]() {
        AssertTrue(Contains(4, subject));
      });
      It("Should return false when called with Contains(5)", [&]() {
        AssertFalse(Contains(5, subject));
      });
      Describe("and we call Remove(1)", [&]() {
        RemoveInPlace(1, subject);
        It("Should return a length of 3", [&]() {
          AssertEquals((size_t)3, Length(subject));
        });
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertTrue(Contains(2, subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(2)", [&]() {
        RemoveInPlace(2, subject);
        It("Should return a length of 2", [&]() {
          AssertEquals((size_t)2, Length(subject));
        });
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(3)", [&]() {
        RemoveInPlace(3, subject);
        It("Should return a length of 1", [&]() {
          AssertEquals((size_t)1, Length(subject));
        });
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(4)", [&]() {
        RemoveInPlace(4, subject);
        It("Should return a length of 0", [&]() {
          AssertEquals((size_t)0, Length(subject));
        });
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(3, subject));
        });
        It("Should return false when called with Contains(4)", [&]() {
          AssertFalse(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
    });
  });
}

}
