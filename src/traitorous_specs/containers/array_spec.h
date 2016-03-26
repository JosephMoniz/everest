#ifndef TRAITOROUS_ARRAY_SPEC_H
#define TRAITOROUS_ARRAY_SPEC_H

#include <containers/array.h>
#include "test/bdd.h"

#include "containers/option.h"
#include "functions/identity.h"

namespace traitorous {

void ArraySpecification() {
  Describe("An Array type", []() {
    It("Should render the correct string when called with Shows()", []{
      auto expected = LocalString("Array(1, 2, 3)");
      auto result   = Show(MakeArray<int, 3>({1, 2, 3}));
      AssertEquals(expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      AssertFalse(Equals(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 3>({4, 5, 6})));
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      AssertTrue(Equals(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      AssertFalse(Equals(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 2>({1, 2})));
    });
    It("Should return false when comparing different arrays with ==", []() {
      AssertFalse((MakeArray<int, 3>({1, 2, 3}) == MakeArray<int, 3>({4, 5, 6})));
    });
    It("Should return true when comparing matching arrays with ==", []() {
      AssertTrue(MakeArray<int, 3>({1, 2, 3}) == MakeArray<int, 3>({1, 2, 3}));
    });
    It("Should return false when comparing different size arrays with ==", []() {
      AssertFalse(MakeArray<int, 3>({1, 2, 3}) == MakeArray<int, 1>({4, 5}));
    });
    It("Should return true when comparing different arrays with !=", []() {
      AssertTrue(MakeArray<int, 3>({1, 2, 3}) != MakeArray<int, 3>({4, 5, 6}));
    });
    It("Should return false when comparing matching arrays with !=", []() {
      AssertFalse(MakeArray<int, 3>({1, 2, 3}) != MakeArray<int, 3>({1, 2, 3}));
    });
    It("Should return true when comparing different size arrays with !=", []() {
      AssertTrue(MakeArray<int, 3>({1, 2, 3}) != MakeArray<int, 1>({4, 5}));
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      AssertEquals(EQUAL, Compare(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return LESS when passing an appropriate array through Compare()", []() {
      AssertEquals(LESS, Compare(MakeArray<int, 3>({1, 1, 3}), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return GREATER when passing an appropriate array through Compare()", []() {
      AssertEquals(GREATER, Compare(MakeArray<int, 2>({1, 3}), MakeArray<int, 2>({1, 2})));
    });
    It("Should return LESS when passing a shorter array through Compare()", []() {
      AssertEquals(LESS, Compare(MakeArray<int, 2>({1, 2}), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return GREATER when passing a longer array through Compare()", []() {
      AssertEquals(GREATER, Compare(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 2>({1, 2})));
    });
    It("Should return the mapped array when called with Map(Add(2))", [](){
      AssertEquals(MakeArray<int, 3>({2, 4, 6}), Map(Multiply(2), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return true when calling Contains() with a contained item", [](){
      AssertTrue(Contains(2, MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      AssertFalse(Contains(6, MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return 3 when calling Length() an array w/ 3 elements", [](){
      AssertEquals((size_t) 3, Length(MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return false when IsEmpty() is called on a non empty array", []() {
      AssertFalse(IsEmpty(MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return true when IsEmpty() is called on an empty array", []() {
      AssertTrue(IsEmpty(MakeArray<int, 0>({})));
    });
    It("Should return a new merged array when calling Add() w/ two arrays", []() {
      auto expected = MakeArray<int, 5>({1, 2, 3, 4, 5});
      auto result   = Add(MakeArray<int, 3>({1, 2, 3}), MakeArray<int, 2>({4, 5}));
      AssertEquals(expected, result);
    });
    It("Should return return an empty array when calling Zero()", []() {
      AssertEquals(MakeArray<int, 0>({}), Zero<Array<int, 0>>());
    });
    It("Should return the sum of the array when called with Fold()", []() {
      AssertEquals(6, Fold(MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the array when called with FoldMap() w/ Identity()", []() {
      AssertEquals(6, FoldMap(Identity<int>(), MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the array when called with FoldR() w/ Add()", []() {
      AssertEquals(6, FoldR(Add<int>(), 0, MakeArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the array when called with FoldL() w/ Add()", []() {
      AssertEquals(6, FoldL(Add<int>(), 0, MakeArray<int, 3>({1, 2, 3})));
    });
  });
}

}

#endif
