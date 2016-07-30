#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/vector.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void VectorSpecification() {
  Describe("An Vector type", []() {
    It("Should render the correct string when called with Shows()", [](){
      auto expected = String("Vector(1, 2, 3)");
      auto result   = Show(Vector<int>({1, 2, 3}));
      auto failure  = "An shared_array of Vector(1, 2, 3) didn't convert to string properly";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when calling Equals() w/ different arrays", [](){
      auto result  = Equals(Vector<int>({1, 2, 3}), Vector<int>({4, 5, 6}));
      auto failure = "Equals(Vector(1, 2, 3), Vector(4, 5, 6)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when calling Equals() w/ similar arrays", [](){
      auto result  = Equals(Vector<int>({1, 2, 3}), Vector<int>({1, 2, 3}));
      auto failure = "Equals(Vector(1, 2, 3), Vector(1, 2, 3)) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false for calling Equals() w/ different sized arrays", []() {
      auto result  = Equals(Vector<int>({1, 2, 3}), Vector<int>({1, 2}));
      auto failure = "Equals(Vector(1, 2, 3), Vector(1, 2)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return false when comparing different arrays with ==", []() {
      auto result  = Vector<int>({1, 2, 3}) == Vector<int>({4, 5, 6});
      auto failure = "Vector(1, 2, 3) == Vector(4, 5, 6) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing matching arrays with ==", []() {
      auto result  = Vector<int>({1, 2, 3}) == Vector<int>({1, 2, 3});
      auto failure = "Vector(1, 2, 3) == Vector(1, 2, 3) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing different size arrays with ==", []() {
      auto result  = Vector<int>({1, 2, 3}) == Vector<int>({4, 5});
      auto failure = "Vector(1, 2, 3) === Vector(4, 5) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different arrays with !=", []() {
      auto result  = Vector<int>({1, 2, 3}) != Vector<int>({4, 5, 6});
      auto failure = "Vector(1, 2, 3) != Vector(4, 5, 6) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return false when comparing matching arrays with !=", []() {
      auto result  = Vector<int>({1, 2, 3}) != Vector<int>({1, 2, 3});
      auto failure = "Vector(1, 2, 3) != Vector(1, 2, 3) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when comparing different size arrays with !=", []() {
      auto result  = Vector<int>({1, 2, 3}) != Vector<int>({4, 5});
      auto failure = "Vector(1, 2, 3) != Vector(4, 5) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return EQUAL when passing matching arrays through Compare()", []() {
      auto expected = Ordering::EQUAL;
      auto result   = Compare(Vector<int>({1, 2, 3}), Vector<int>({1, 2, 3}));
      auto failure  = "Compare(Vector(1, 2, 3), Vector(1, 2, 3)) did not return Ordering::EQUAL";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing an appropriate vector through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(Vector<int>({1, 1, 3}), Vector<int>({1, 2, 3}));
      auto failure  = "Compare(Vector(1, 1, 3), Vector(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing an appropriate vector through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(Vector<int>({1, 3}), Vector<int>({1, 2}));
      auto failure  = "Compare(Vector(1, 3), Vector(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return LESS when passing a shorter vector through Compare()", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(Vector<int>({1, 2}), Vector<int>({1, 2, 3}));
      auto failure  = "Compare(Vector(1, 2), Vector(1, 2, 3)) did not return Ordering::LESS";
      AssertEquals(failure, expected, result);
    });
    It("Should return GREATER when passing a longer vector through Compare()", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(Vector<int>({1, 2, 3}), Vector<int>({1, 2}));
      auto failure  = "Compare(Vector(1, 2, 3), Vector(1, 2)) did not return Ordering::GREATER";
      AssertEquals(failure, expected, result);
    });
    It("Should return the mapped vector when called with Map(Add(2))", [](){
      auto expected = Vector<int>({2, 4, 6});
      auto result   = Map(Multiply(2), Vector<int>({1, 2, 3}));
      auto failure  = "Map(Multiply(2), Vector(1, 2, 3)) did not return Vector(2, 4, 6)";
      AssertEquals(failure, expected, result);
    });
    It("Should return true when calling Contains() with a contained item", [](){
      auto result  = Contains(2, Vector<int>({1, 2, 3}));
      auto failure = "Contains(1, Vector(1, 2, 3)) did not evaluate to true";
      AssertTrue(failure, result);
    });
    It("Should return false when calling Contains() with a non contained item", [](){
      auto result  = Contains(6, Vector<int>({1, 2, 3}));
      auto failure = "Contains(6, Vector(1, 2, 3)) did not evaluate to false";
      AssertFalse(failure, result);
    });
    It("Should return 3 when calling Length() an vector w/ 3 elements", [](){
      auto expected = (size_t) 3;
      auto result   = Length(Vector<int>({1, 2, 3}));
      auto failure  = "Length(Vector(1, 2, 3)) did not return 3";
      AssertEquals(failure, expected, result);
    });
    It("Should return false when IsEmpty() is called on a non empty vector", []() {
      auto result  = IsEmpty(Vector<int>({1, 2, 3}));
      auto failure = "IsEmpty(Vector(1, 2, 3)) evaluated to true";
      AssertFalse(failure, result);
    });
    It("Should return true when IsEmpty() is called on an empty vector", []() {
      auto result  = IsEmpty(Vector<int>({}));
      auto failure = "IsEmpty(Vector()) evaluated to false";
      AssertTrue(failure, result);
    });
    It("Should return a new merged vector when calling Add() w/ two arrays", []() {
      auto expected = Vector<int>({1, 2, 3, 4, 5});
      auto result   = Add(Vector<int>({1, 2, 3}), Vector<int>({4, 5}));
      auto failure  = "Add(Vector(1, 2, 3), Vector(4, 5)) did not return Vector(1, 2, 3, 4, 5)";
      AssertEquals(failure, expected, result);
    });
    It("Should return return an empty vector when calling Zero()", []() {
      auto expected = Vector<int>({});
      auto result   = Zero<Vector<int>>();
      auto failure  = "Zero<Vector<int, 0>>() did not return Vector()";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the vector when called with Fold()", []() {
      auto expected = 6;
      auto result   = Fold(Vector<int>({1, 2, 3}));
      auto failure  = "Fold(Vector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the vector when called with FoldMap() w/ Identity()", []() {
      auto expected = 6;
      auto result   = FoldMap(Identity<int>(), Vector<int>({1, 2, 3}));
      auto failure  = "FoldMap(Identity, Vector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the vector when called with FoldR() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldR(Add<int>(), 0, Vector<int>({1, 2, 3}));
      auto failure  = "FoldR(Add(), 0, Vector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
    It("Should return the sum of the vector when called with FoldL() w/ Add()", []() {
      auto expected = 6;
      auto result   = FoldL(Add<int>(), 0, Vector<int>({1, 2, 3}));
      auto failure  = "FoldL(Add(), 0, Vector(1, 2, 3)) did not return 6";
      AssertEquals(failure, expected, result);
    });
  });
}

}