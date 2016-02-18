#ifndef TRAITOROUS_LOCAL_LIST_SPEC_H
#define TRAITOROUS_LOCAL_LIST_SPEC_H

#include "containers/list.h"
#include "test/bdd.h"

#include "functions/identity.h"

namespace traitorous {

void ListSpecification() {
  Describe("A List type", []() {
    It("Should render the correct string when called with Shows()", []() {
      return Show(Cons(1, Cons(2))) == "List(1, 2)";
    });
    It("Should return true when Equals() is called w/ matching single item lists", []() {
      return Equals(Cons(1), Cons(1));
    });
    It("Should return false when Equals() is called w/ non-matching single item lists", []() {
      return !Equals(Cons(1), Cons(2));
    });
    It("Should return true when Equals() is called w/ matching lists", []() {
      return Equals(Cons(1, Cons(2)), Cons(1, Cons(2)));
    });
    It("Should return false when Equals() is called w/ non-matching lists", []() {
      return !Equals(Cons(1, Cons(2)), Cons(1, Cons(3)));
    });
    It("Should return false when comparing different lists with ==", []() {
      return !(Cons(1, Cons(2)) == Cons(1, Cons(4)));
    });
    It("Should return true when comparing matching lists with ==", []() {
      return Cons(1, Cons(2)) == Cons(1, Cons(2));
    });
    It("Should return true when comparing different lists with !=", []() {
      return Cons(1, Cons(2)) != Cons(1, Cons(4));
    });
    It("Should return false when comparing matching lists with !=", []() {
      return !(Cons(1, Cons(2)) != Cons(1, Cons(2)));
    });
    It("Should return EQUAL when passing matching lists through Compare()", []() {
      return Compare(Cons(1, Cons(2)), Cons(1, Cons(2))) == EQUAL;
    });
    It("Should return LESS when passing an appropriate list through Compare()", []() {
      return Compare(Cons(1, Cons(1)), Cons(1, Cons(2))) == LESS;
    });
    It("Should return GREATER when passing an appropriate list through Compare()", []() {
      return Compare(Cons(1, Cons(3)), Cons(1, Cons(2))) == GREATER;
    });
    It("Should return the mapped list when called with Map(Multiply(2))", []() {
      return Map(Multiply(2), Cons(1, Cons(2))) == Cons(2, Cons(4));
    });
    It("Should return true when calling Contains() with a contained item", [](){
      return Contains(2, Cons(1, Cons(2, Cons(3))));
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      return !Contains(6, Cons(1, Cons(2, Cons(3))));
    });
    It("Should return 3 when calling Length() an list w/ 3 elements", [](){
      return Length(Cons(1, Cons(2, Cons(3)))) == 3;
    });
    It("Should return false when IsEmpty() is called on a non empty list", []() {
      return !IsEmpty(Cons(1, Cons(2, Cons(3))));
    });
    It("Should return true when IsEmpty() is called on an empty list", []() {
      return IsEmpty(Cons<int>());
    });
    It("Should return a new merged array when calling Add() w/ two arrays", []() {
      auto expected = Cons(1, Cons(2, Cons(3, Cons(4, Cons(5, Cons(6))))));
      auto result   = Add(Cons(1, Cons(2, Cons(3))), Cons(4, Cons(5, Cons(6))));
      return result == expected;
    });
    It("Should return return an empty list when calling Zero()", []() {
      return Zero<List<int>>() == Cons<int>();
    });
  });
}

}

#endif
