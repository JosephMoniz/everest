#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/mutable_containers/vector/all_traits.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void MutableVectorSpecification() {
  Describe("A MutableVector type", []() {
    It("Should render the correct string when called with Shows()", [](){
      auto expected = String("MutableVector(1, 2, 3)");
      auto result   = Show(MutableVector<int>({1, 2, 3}));
      auto failure  = "An shared_array of MutableVector(1, 2, 3) didn't convert to string properly";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(MutableVector<int>({1, 2, 3}), MutableVector<int>({4, 5, 6}));
      auto failure = "Equals(MutableVector(1, 2, 3), MutableVector(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(MutableVector<int>({1, 2, 3}), MutableVector<int>({1, 2, 3}));
      auto failure = "Equals(MutableVector(1, 2, 3), MutableVector(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(MutableVector<int>({1, 2, 3}), MutableVector<int>({1, 2}));
      auto failure = "Equals(MutableVector(1, 2, 3), MutableVector(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = MutableVector<int>({1, 2, 3}) == MutableVector<int>({4, 5, 6});
      auto failure = "MutableVector(1, 2, 3) == MutableVector(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = MutableVector<int>({1, 2, 3}) == MutableVector<int>({1, 2, 3});
      auto failure = "MutableVector(1, 2, 3) == MutableVector(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = MutableVector<int>({1, 2, 3}) == MutableVector<int>({4, 5});
      auto failure = "MutableVector(1, 2, 3) === MutableVector(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = MutableVector<int>({1, 2, 3}) != MutableVector<int>({4, 5, 6});
      auto failure = "MutableVector(1, 2, 3) != MutableVector(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = MutableVector<int>({1, 2, 3}) != MutableVector<int>({1, 2, 3});
      auto failure = "MutableVector(1, 2, 3) != MutableVector(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = MutableVector<int>({1, 2, 3}) != MutableVector<int>({4, 5});
      auto failure = "MutableVector(1, 2, 3) != MutableVector(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      auto expected = Ordering::EQUAL;
      auto result   = Compare(MutableVector<int>({1, 2, 3}), MutableVector<int>({1, 2, 3}));
      auto failure  = "Compare(MutableVector(1, 2, 3), MutableVector(1, 2, 3)) did not return Ordering::EQUAL";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing an appropriate MutableVector through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(MutableVector<int>({1, 1, 3}), MutableVector<int>({1, 2, 3}));
      auto failure  = "Compare(MutableVector(1, 1, 3), MutableVector(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing an appropriate MutableVector through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(MutableVector<int>({1, 3}), MutableVector<int>({1, 2}));
      auto failure  = "Compare(MutableVector(1, 3), MutableVector(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing a shorter MutableVector through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(MutableVector<int>({1, 2}), MutableVector<int>({1, 2, 3}));
      auto failure  = "Compare(MutableVector(1, 2), MutableVector(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing a longer MutableVector through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(MutableVector<int>({1, 2, 3}), MutableVector<int>({1, 2}));
      auto failure  = "Compare(MutableVector(1, 2, 3), MutableVector(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return the mapped MutableVector when called with Map(Add(2))", [](){
      auto expected = MutableVector<int>({2, 4, 6});
      auto result   = Map(Multiply(2), MutableVector<int>({1, 2, 3}));
      auto failure  = "Map(Multiply(2), MutableVector(1, 2, 3)) did not return MutableVector(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, MutableVector<int>({1, 2, 3}));
      auto failure = "Contains(1, MutableVector(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, MutableVector<int>({1, 2, 3}));
      auto failure = "Contains(6, MutableVector(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an MutableVector w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(MutableVector<int>({1, 2, 3}));
      auto failure  = "Length(MutableVector(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty MutableVector", []() {
      auto result  = IsEmpty(MutableVector<int>({1, 2, 3}));
      auto failure = "IsEmpty(MutableVector(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty MutableVector", []() {
      auto result  = IsEmpty(MutableVector<int>({}));
      auto failure = "IsEmpty(MutableVector()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged MutableVector when calling Add() w/ two arrays", []() {
      auto expected = MutableVector<int>({1, 2, 3, 4, 5});
      auto result   = Add(MutableVector<int>({1, 2, 3}), MutableVector<int>({4, 5}));
      auto failure  = "Add(MutableVector(1, 2, 3), MutableVector(4, 5)) did not return MutableVector(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty MutableVector when calling Zero()", []() {
      auto expected = MutableVector<int>({});
      auto result   = Zero<MutableVector<int>>();
      auto failure  = "Zero<MutableVector<int, 0>>() did not return MutableVector()";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the MutableVector when called with Fold()", []() {
      auto expected = 6;
      auto result   = Fold(MutableVector<int>({1, 2, 3}));
      auto failure  = "Fold(MutableVector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the MutableVector when called with FoldMap() w/ Identity()", []() {
      auto expected = 6;
      auto result   = FoldMap(Identity<int>(), MutableVector<int>({1, 2, 3}));
      auto failure  = "FoldMap(Identity, MutableVector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the MutableVector when called with FoldR() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldR(Add<int>(), 0, MutableVector<int>({1, 2, 3}));
      auto failure  = "FoldR(Add(), 0, MutableVector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the MutableVector when called with FoldL() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldL(Add<int>(), 0, MutableVector<int>({1, 2, 3}));
      auto failure  = "FoldL(Add(), 0, MutableVector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for a null vector", []() {
      auto expected = (size_t) 0;
      auto result     = Length(MutableVector<int>());
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for an empty vector", []() {
      auto expected   = (size_t) 0;
      auto result     = Length(MutableVector<int>(32));
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 3 for a vector with three elements", []() {
      auto subject = MutableVector<int>();
      PushInPlace(1, subject);
      PushInPlace(2, subject);
      PushInPlace(3, subject);
      auto expected   = (size_t) 3;
      auto result     = Length(subject);
      auto failure    = "The vector returned the incorrect length";
      AssertEquals(failure, expected, result);
    });
    Describe("of [1,2,3,4] called with FilterInPlace(n % 2 == 0)", []() {
      auto subject = MutableVector<int>();
      PushInPlace(1, subject);
      PushInPlace(2, subject);
      PushInPlace(3, subject);
      PushInPlace(4, subject);
      FilterInPlace([](auto n) { return n % 2 == 0; }, subject);
      It("Should be of length 2", [&]() {
        AssertEquals((size_t) 2, Length(subject));
      });
      It("Should return 2 for the first element", [&]() {
        AssertEquals(2, Pointer(subject)[0]);
      });
      It("Should return 4 for the second element", [&]() {
        AssertEquals(4, Pointer(subject)[1]);
      });
    });
    Describe("of [1,2,3] called with InsertInPlace(0, 0)", []() {
      It("Should return a vector of [0,1,2,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3});
        InsertInPlace(0, 0, subject);
        AssertEquals(MutableVector<int>({0, 1, 2, 3}), subject);
      });
    });
    Describe("of [1,2,3,4] called with InsertInPlace(0, 1)", []() {
      It("Should return a vector of [1,0,2,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3, 4});
        InsertInPlace(0, 1, subject);
        AssertEquals(MutableVector<int>({1, 0, 2, 3, 4}), subject);
      });
    });
    Describe("of [1,2,3,4] called with InsertInPlace(0, 2)", []() {
      It("Should return a vector of [1,2,0,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3, 4});
        InsertInPlace(0, 2, subject);
        AssertEquals(MutableVector<int>({1, 2, 0, 3, 4}), subject);
      });
    });
    Describe("of [1,2,3,4] called with InsertInPlace(0, 3)", []() {
      It("Should return a vector of [1,2,3,0]", []() {
        auto subject = MutableVector<int>({1, 2, 3, 4});
        InsertInPlace(0, 3, subject);
        AssertEquals(MutableVector<int>({1, 2, 3, 0, 4}), subject);
      });
    });
    Describe("of [1,2,3,4] called with InsertInPlace(0, 4)", []() {
      It("Should return a vector of [1,2,3,0]", []() {
        auto subject = MutableVector<int>({1, 2, 3, 4});
        InsertInPlace(0, 4, subject);
        AssertEquals(MutableVector<int>({1, 2, 3, 4, 0}), subject);
      });
    });
    Describe("of [1,2,3] called with RemoveAtInPlace(0)", []() {
      It("Should return a vector of [2,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3});
        RemoveAtInPlace(0, subject);
        AssertEquals(MutableVector<int>({2, 3}), subject);
      });
    });
    Describe("of [1,2,3] called with RemoveAtInPlace(1)", []() {
      It("Should return a vector of [1,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3});
        RemoveAtInPlace(1, subject);
        AssertEquals(MutableVector<int>({1, 3}), subject);
      });
    });
    Describe("of [1,2,3] called with RemoveAtInPlace(2)", []() {
      It("Should return a vector of [1,2]", []() {
        auto subject = MutableVector<int>({1, 2, 3});
        RemoveAtInPlace(2, subject);
        AssertEquals(MutableVector<int>({1, 2}), subject);
      });
    });
    Describe("of [1,2,3] called with RemoveAtInPlace(3)", []() {
      It("Should return a vector of [1,2,3]", []() {
        auto subject = MutableVector<int>({1, 2, 3});
        RemoveAtInPlace(3, subject);
        AssertEquals(MutableVector<int>({1, 2, 3}), subject);
      });
    });
  });
}

}

