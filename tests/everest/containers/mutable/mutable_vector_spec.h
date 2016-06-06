#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

void MutableVectorSpecification() {
  Describe("A MutableVector type", []() {
    It("Should return length 0 for a null vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableVector<int>());
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 0 for an empty vector", []() {
      size_t expected = 0;
      auto result     = Length(MutableVector<int>(32));
      auto failure    = "An empty vector should have a length of 0";
      AssertEquals(failure, expected, result);
    });
    It("Should return length 3 for a vector with three elements", []() {
      auto subject = MutableVector<int>();
      PushInPlace(1, subject);
      PushInPlace(2, subject);
      PushInPlace(3, subject);
      size_t expected = 3;
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
        AssertEquals((size_t)2, Length(subject));
      });
      It("Should return 2 for the first element", [&]() {
        AssertEquals(2, Pointer(subject)[0]);
      });
      It("Should return 4 for the second element", [&]() {
        AssertEquals(4, Pointer(subject)[1]);
      });
    });
  });
}

}

