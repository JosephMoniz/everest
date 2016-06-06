#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/array.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

void ArraySpecification() {
  Describe("An Array type", []() {
    It("Should render the correct string when called with Shows()", [](){
      auto expected = String("Array(1, 2, 3)");
      auto result   = Show(Array<int, 3>({1, 2, 3}));
      auto failure  = "An shared_array of Array(1, 2, 3) didn't convert to string properly";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(Array<int, 3>({1, 2, 3}), Array<int, 3>({4, 5, 6}));
      auto failure = "Equals(Array(1, 2, 3), Array(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(Array<int, 3>({1, 2, 3}), Array<int, 3>({1, 2, 3}));
      auto failure = "Equals(Array(1, 2, 3), Array(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(Array<int, 3>({1, 2, 3}), Array<int, 2>({1, 2}));
      auto failure = "Equals(Array(1, 2, 3), Array(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = Array<int, 3>({1, 2, 3}) == Array<int, 3>({4, 5, 6});
      auto failure = "Array(1, 2, 3) == Array(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = Array<int, 3>({1, 2, 3}) == Array<int, 3>({1, 2, 3});
      auto failure = "Array(1, 2, 3) == Array(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = Array<int, 3>({1, 2, 3}) == Array<int, 2>({4, 5});
      auto failure = "Array(1, 2, 3) === Array(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = Array<int, 3>({1, 2, 3}) != Array<int, 3>({4, 5, 6});
      auto failure = "Array(1, 2, 3) != Array(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = Array<int, 3>({1, 2, 3}) != Array<int, 3>({1, 2, 3});
      auto failure = "Array(1, 2, 3) != Array(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = Array<int, 3>({1, 2, 3}) != Array<int, 2>({4, 5});
      auto failure = "Array(1, 2, 3) != Array(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      auto expected = Ordering::EQUAL;
      auto result   = Compare(Array<int, 3>({1, 2, 3}), Array<int, 3>({1, 2, 3}));
      auto failure  = "Compare(Array(1, 2, 3), Array(1, 2, 3)) did not return Ordering::EQUAL";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing an appropriate shared_array through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(Array<int, 3>({1, 1, 3}), Array<int, 3>({1, 2, 3}));
      auto failure  = "Compare(Array(1, 1, 3), Array(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing an appropriate shared_array through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(Array<int, 2>({1, 3}), Array<int, 2>({1, 2}));
      auto failure  = "Compare(Array(1, 3), Array(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing a shorter shared_array through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(Array<int, 2>({1, 2}), Array<int, 3>({1, 2, 3}));
      auto failure  = "Compare(Array(1, 2), Array(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing a longer shared_array through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(Array<int, 3>({1, 2, 3}), Array<int, 2>({1, 2}));
      auto failure  = "Compare(Array(1, 2, 3), Array(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return the mapped shared_array when called with Map(Add(2))", [](){
      auto expected = MakeSharedArray<int, 3>({2, 4, 6});
      auto result   = Map(Multiply(2), Array<int, 3>({1, 2, 3}));
      auto failure  = "Map(Multiply(2), Array(1, 2, 3)) did not return Array(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, Array<int, 3>({1, 2, 3}));
      auto failure = "Contains(1, Array(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, Array<int, 3>({1, 2, 3}));
      auto failure = "Contains(6, Array(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an shared_array w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(Array<int, 3>({1, 2, 3}));
      auto failure  = "Length(Array(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty shared_array", []() {
      auto result  = IsEmpty(Array<int, 3>({1, 2, 3}));
      auto failure = "IsEmpty(Array(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty shared_array", []() {
      auto result  = IsEmpty(Array<int, 0>({}));
      auto failure = "IsEmpty(Array()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged shared_array when calling Add() w/ two arrays", []() {
      auto expected = MakeSharedArray<int, 5>({1, 2, 3, 4, 5});
      auto result   = Add(Array<int, 3>({1, 2, 3}), Array<int, 2>({4, 5}));
      auto failure  = "Add(Array(1, 2, 3), Array(4, 5)) did not return Array(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty shared_array when calling Zero()", []() {
      auto expected = Array<int, 0>({});
      auto result   = Zero<Array<int, 0>>();
      auto failure  = "Zero<Array<int, 0>>() did not return Array()";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the shared_array when called with Fold()", []() {
      auto expected = 6;
      auto result   = Fold(Array<int, 3>({1, 2, 3}));
      auto failure  = "Fold(Array(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the shared_array when called with FoldMap() w/ Identity()", []() {
      auto expected = 6;
      auto result   = FoldMap(Identity<int>(), Array<int, 3>({1, 2, 3}));
      auto failure  = "FoldMap(Identity, Array(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the shared_array when called with FoldR() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldR(Add<int>(), 0, Array<int, 3>({1, 2, 3}));
      auto failure  = "FoldR(Add(), 0, Array(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the shared_array when called with FoldL() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldL(Add<int>(), 0, Array<int, 3>({1, 2, 3}));
      auto failure  = "FoldL(Add(), 0, Array(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
  });
}

}

