#ifndef TRAITOROUS_LOCAL_ARRAY_SPEC_H
#define TRAITOROUS_LOCAL_ARRAY_SPEC_H

#include <containers/array.h>
#include "test/bdd.h"

#include "containers/local_option.h"
#include "functions/identity.h"

namespace traitorous {

void LocalArraySpecification() {
  Describe("An LocalArray type", []() {
    It("Should render the correct string when called with Shows()", [](){
      return Show(LocalArray<int, 3>({1, 2, 3})) == "LocalArray(1, 2, 3)";
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      return !Equals(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 3>({4, 5, 6}));
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      return Equals(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 3>({1, 2, 3}));
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      return !Equals(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 2>({1, 2}));
    });
    It("Should return false when comparing different arrays with ==", []() {
      return !(LocalArray<int, 3>({1, 2, 3}) == LocalArray<int, 3>({4, 5, 6}));
    });
    It("Should return true when comparing matching arrays with ==", []() {
      return LocalArray<int, 3>({1, 2, 3}) == LocalArray<int, 3>({1, 2, 3});
    });
    It("Should return false when comparing different size arrays with ==", []() {
      return !(LocalArray<int, 3>({1, 2, 3}) == LocalArray<int, 1>({4, 5}));
    });
    It("Should return true when comparing different arrays with !=", []() {
      return LocalArray<int, 3>({1, 2, 3}) != LocalArray<int, 3>({4, 5, 6});
    });
    It("Should return false when comparing matching arrays with !=", []() {
      return !(LocalArray<int, 3>({1, 2, 3}) != LocalArray<int, 3>({1, 2, 3}));
    });
    It("Should return true when comparing different size arrays with !=", []() {
      return MakeArray<int, 3>({1, 2, 3}) != MakeArray<int, 1>({4, 5});
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      return Compare(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 3>({1, 2, 3})) == EQUAL;
    });
    It("Should return LESS when passing an appropriate array through Compare()", []() {
      return Compare(LocalArray<int, 3>({1, 1, 3}), LocalArray<int, 3>({1, 2, 3})) == LESS;
    });
    It("Should return GREATER when passing an appropriate array through Compare()", []() {
      return Compare(LocalArray<int, 2>({1, 3}), LocalArray<int, 2>({1, 2})) == GREATER;
    });
    It("Should return LESS when passing a shorter array through Compare()", []() {
      return Compare(LocalArray<int, 2>({1, 2}), LocalArray<int, 3>({1, 2, 3})) == LESS;
    });
    It("Should return GREATER when passing a longer array through Compare()", []() {
      return Compare(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 2>({1, 2})) == GREATER;
    });
    It("Should return the mapped array when called with Map(Add(2))", [](){
      return Map(Multiply(2), LocalArray<int, 3>({1, 2, 3})) == MakeArray<int, 3>({2, 4, 6});
    });
    It("Should return true when calling Contains() with a contained item", [](){
      return Contains(2, LocalArray<int, 3>({1, 2, 3}));
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      return !Contains(6, LocalArray<int, 3>({1, 2, 3}));
    });
    It("Should return 3 when calling Length() an array w/ 3 elements", [](){
      return Length(LocalArray<int, 3>({1, 2, 3})) == 3;
    });
    It("Should return false when IsEmpty() is called on a non empty array", []() {
      return !IsEmpty(LocalArray<int, 3>({1, 2, 3}));
    });
    It("Should return true when IsEmpty() is called on an empty array", []() {
      return IsEmpty(LocalArray<int, 0>({}));
    });
    It("Should return a new merged array when calling Add() w/ two arrays", []() {
      auto expected = MakeArray<int, 5>({1, 2, 3, 4, 5});
      auto result   = Add(LocalArray<int, 3>({1, 2, 3}), LocalArray<int, 2>({4, 5}));
      return result == expected;
    });
    It("Should return return an empty array when calling Zero()", []() {
      return Zero<LocalArray<int, 0>>() == LocalArray<int, 0>({});
    });
  });
}

}

#endif
