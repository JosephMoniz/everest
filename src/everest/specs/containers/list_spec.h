#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/list.h>
#include <everest/functions/identity.h>
#include <everest/types/int32.h>

namespace traitorous {

void ListSpecification() {
  Describe("A List type", []() {
    It("Should render the correct string when called with Shows()", []() {
      AssertEquals(String("List(1, 2)"), Show(Cons(1, Cons(2))));
    });
    It("Should return true when Equals() is called w/ matching single item lists", []() {
      AssertTrue(Equals(Cons(1), Cons(1)));
    });
    It("Should return false when Equals() is called w/ non-matching single item lists", []() {
      AssertFalse(Equals(Cons(1), Cons(2)));
    });
    It("Should return true when Equals() is called w/ matching lists", []() {
      AssertTrue(Equals(Cons(1, Cons(2)), Cons(1, Cons(2))));
    });
    It("Should return false when Equals() is called w/ non-matching lists", []() {
      AssertFalse(Equals(Cons(1, Cons(2)), Cons(1, Cons(3))));
    });
    It("Should return false when comparing different lists with ==", []() {
      AssertFalse(Cons(1, Cons(2)) == Cons(1, Cons(4)));
    });
    It("Should return true when comparing matching lists with ==", []() {
      AssertTrue(Cons(1, Cons(2)) == Cons(1, Cons(2)));
    });
    It("Should return true when comparing different lists with !=", []() {
      AssertTrue(Cons(1, Cons(2)) != Cons(1, Cons(4)));
    });
    It("Should return false when comparing matching lists with !=", []() {
      AssertFalse(Cons(1, Cons(2)) != Cons(1, Cons(2)));
    });
    It("Should return EQUAL when passing matching lists through Compare()", []() {
      AssertEquals(Ordering::EQUAL, Compare(Cons(1, Cons(2)), Cons(1, Cons(2))));
    });
    It("Should return LESS when passing an appropriate list through Compare()", []() {
      AssertEquals(Ordering::LESS, Compare(Cons(1, Cons(1)), Cons(1, Cons(2))));
    });
    It("Should return GREATER when passing an appropriate list through Compare()", []() {
      AssertEquals(Ordering::GREATER, Compare(Cons(1, Cons(3)), Cons(1, Cons(2))));
    });
    It("Should return the mapped list when called with Map(Multiply(2))", []() {
      AssertEquals(Cons(2, Cons(4)), Map(Multiply(2), Cons(1, Cons(2))));
    });
    It("Should return true when calling Contains() with a contained item", [](){
      AssertTrue(Contains(2, Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      AssertFalse(Contains(6, Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return 3 when calling Length() an list w/ 3 elements", [](){
      AssertEquals((size_t) 3, Length(Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return false when IsEmpty() is called on a non empty list", []() {
      AssertFalse(IsEmpty(Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return true when IsEmpty() is called on an empty list", []() {
      AssertTrue(IsEmpty(Cons<int>()));
    });
    It("Should return a new merged array when calling Add() w/ two arrays", []() {
      auto expected = Cons(1, Cons(2, Cons(3, Cons(4, Cons(5, Cons(6))))));
      auto result   = Add(Cons(1, Cons(2, Cons(3))), Cons(4, Cons(5, Cons(6))));
      AssertEquals(expected, result);
    });
    It("Should return return an empty list when calling Zero()", []() {
      AssertEquals(Cons<int>(), Zero<List<int>>());
    });
    It("Should return the sum of the list when called with Fold()", []() {
      AssertEquals(6, Fold(Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return the sum of the list when called with FoldMap() w/ Identity()", []() {
      AssertEquals(6, FoldMap(Identity<int>(), Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return the sum of the list when called with FoldR() w/ Add()", []() {
      AssertEquals(6, FoldR(Add<int>(), 0, Cons(1, Cons(2, Cons(3)))));
    });
    It("Should return the sum of the list when called with FoldL() w/ Add()", []() {
      AssertEquals(6, FoldL(Add<int>(), 0, Cons(1, Cons(2, Cons(3)))));
    });
  });
}

}