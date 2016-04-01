#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/array.h>

namespace traitorous {

void SharedArraySpecification() {
  Describe("An SharedArray type", []() {
    It("Should render the correct string when called with Shows()", []{
      auto expected = String("SharedArray(1, 2, 3)");
      auto result   = Show(MakeSharedArray<int, 3>({1, 2, 3}));
      AssertEquals(expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      AssertFalse(Equals(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 3>({4, 5, 6})));
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      AssertTrue(Equals(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      AssertFalse(Equals(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 2>({1, 2})));
    });
    It("Should return false when comparing different arrays with ==", []() {
      AssertFalse((MakeSharedArray<int, 3>({1, 2, 3}) == MakeSharedArray<int, 3>({4, 5, 6})));
    });
    It("Should return true when comparing matching arrays with ==", []() {
      AssertTrue(MakeSharedArray<int, 3>({1, 2, 3}) == MakeSharedArray<int, 3>({1, 2, 3}));
    });
    It("Should return false when comparing different size arrays with ==", []() {
      AssertFalse(MakeSharedArray<int, 3>({1, 2, 3}) == MakeSharedArray<int, 2>({4, 5}));
    });
    It("Should return true when comparing different arrays with !=", []() {
      AssertTrue(MakeSharedArray<int, 3>({1, 2, 3}) != MakeSharedArray<int, 3>({4, 5, 6}));
    });
    It("Should return false when comparing matching arrays with !=", []() {
      AssertFalse(MakeSharedArray<int, 3>({1, 2, 3}) != MakeSharedArray<int, 3>({1, 2, 3}));
    });
    It("Should return true when comparing different size arrays with !=", []() {
      AssertTrue(MakeSharedArray<int, 3>({1, 2, 3}) != MakeSharedArray<int, 2>({4, 5}));
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      AssertEquals(Ordering::EQUAL, Compare(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return LESS when passing an appropriate shared_array through Compare()", []() {
      AssertEquals(Ordering::LESS, Compare(MakeSharedArray<int, 3>({1, 1, 3}), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return GREATER when passing an appropriate shared_array through Compare()", []() {
      AssertEquals(Ordering::GREATER, Compare(MakeSharedArray<int, 2>({1, 3}), MakeSharedArray<int, 2>({1, 2})));
    });
    It("Should return LESS when passing a shorter shared_array through Compare()", []() {
      AssertEquals(Ordering::LESS, Compare(MakeSharedArray<int, 2>({1, 2}), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return GREATER when passing a longer shared_array through Compare()", []() {
      AssertEquals(Ordering::GREATER, Compare(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 2>({1, 2})));
    });
    It("Should return the mapped shared_array when called with Map(Add(2))", [](){
      AssertEquals(MakeSharedArray<int, 3>({2, 4, 6}), Map(Multiply(2), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return true when calling Contains() with a contained item", [](){
      AssertTrue(Contains(2, MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      AssertFalse(Contains(6, MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return 3 when calling Length() an shared_array w/ 3 elements", [](){
      AssertEquals((size_t) 3, Length(MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return false when IsEmpty() is called on a non empty shared_array", []() {
      AssertFalse(IsEmpty(MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return true when IsEmpty() is called on an empty shared_array", []() {
      AssertTrue(IsEmpty(MakeSharedArray<int, 0>({})));
    });
    It("Should return a new merged shared_array when calling Add() w/ two arrays", []() {
      auto expected = MakeSharedArray<int, 5>({1, 2, 3, 4, 5});
      auto result   = Add(MakeSharedArray<int, 3>({1, 2, 3}), MakeSharedArray<int, 2>({4, 5}));
      AssertEquals(expected, result);
    });
    It("Should return return an empty shared_array when calling Zero()", []() {
      AssertEquals(MakeSharedArray<int, 0>({}), Zero<SharedArray<int, 0>>());
    });
    It("Should return the sum of the shared_array when called with Fold()", []() {
      AssertEquals(6, Fold(MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the shared_array when called with FoldMap() w/ Identity()", []() {
      AssertEquals(6, FoldMap(Identity<int>(), MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the shared_array when called with FoldR() w/ Add()", []() {
      AssertEquals(6, FoldR(Add<int>(), 0, MakeSharedArray<int, 3>({1, 2, 3})));
    });
    It("Should return the sum of the shared_array when called with FoldL() w/ Add()", []() {
      AssertEquals(6, FoldL(Add<int>(), 0, MakeSharedArray<int, 3>({1, 2, 3})));
    });
  });
}

}
