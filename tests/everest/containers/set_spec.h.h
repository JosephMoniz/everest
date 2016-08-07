#pragma once

#include <everest/test/bdd.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/containers/set.h>
#include <everest/containers/set/all_traits.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

void SetSpecification() {
  Describe("A Set type", []() {
    It("Should render the correct string when called with Shows()", [](){
      auto expected = String("Set(1, 2, 3)");
      auto result   = Show(Set<int>(1, 2, 3));
      auto failure  = "An of Set(1, 2, 3) didn't convert to string properly";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(Set<int>(1, 2, 3), Set<int>(4, 5, 6));
      auto failure = "Equals(Set(1, 2, 3), Set(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(Set<int>(1, 2, 3), Set<int>(1, 2, 3));
      auto failure = "Equals(Set(1, 2, 3), Set(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(Set<int>(1, 2, 3), Set<int>(1, 2));
      auto failure = "Equals(Set(1, 2, 3), Set(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = Set<int>(1, 2, 3) == Set<int>(4, 5, 6);
      auto failure = "Set(1, 2, 3) == Set(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = Set<int>(1, 2, 3) == Set<int>(1, 2, 3);
      auto failure = "Set(1, 2, 3) == Set(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = Set<int>(1, 2, 3) == Set<int>(4, 5);
      auto failure = "Set(1, 2, 3) === Set(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = Set<int>(1, 2, 3) != Set<int>(4, 5, 6);
      auto failure = "Set(1, 2, 3) != Set(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = Set<int>(1, 2, 3) != Set<int>(1, 2, 3);
      auto failure = "Set(1, 2, 3) != Set(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = Set<int>(1, 2, 3) != Set<int>(4, 5);
      auto failure = "Set(1, 2, 3) != Set(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return the mapped Set when called with Map(Add(2))", [](){
      auto expected = Set<int>(2, 4, 6);
      auto result   = Map(Multiply(2), Set<int>(1, 2, 3));
      auto failure  = "Map(Multiply(2), Set(1, 2, 3)) did not return Set(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, Set<int>(1, 2, 3));
      auto failure = "Contains(1, Set(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, Set<int>(1, 2, 3));
      auto failure = "Contains(6, Set(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an Set w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(Set<int>(1, 2, 3));
      auto failure  = "Length(Set(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty Set", []() {
      auto result  = IsEmpty(Set<int>(1, 2, 3));
      auto failure = "IsEmpty(Set(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty Set", []() {
      auto result  = IsEmpty(Set<int>());
      auto failure = "IsEmpty(Set()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged Set when calling Add() w/ another set", []() {
      auto expected = Set<int>(1, 2, 3, 4, 5);
      auto result   = Add(Set<int>(1, 2, 3), Set<int>(4, 5));
      auto failure  = "Add(Set(1, 2, 3), Set(4, 5)) did not return Set(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty Set when calling Zero()", []() {
      auto expected = Set<int>();
      auto result   = Zero<Set<int>>();
      auto failure  = "Zero<Set<int, 0>>() did not return Set()";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for a null set", []() {
      auto  expected  = (size_t) 0;
      auto result     = Length(Set<int>());
      auto failure    = "An empty set should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for an empty set", []() {
      auto expected   = (size_t) 0;
      auto result     = Length(Set<int>());
      auto failure    = "An empty set should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 3 for a set with three elements", []() {
      auto subject    = Set<int>(1, 2, 3);
      auto expected   = (size_t) 3;
      auto result     = Length(subject);
      auto failure    = "The set returned the incorrect length";
      AssertEquals(failure, expected, result);
    });
    Describe("of value {1, 2, 3, 4}", []() {
      auto subject = Set<int>(1, 2, 3, 4);
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
    });
  });
}

}