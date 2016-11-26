#pragma once

#include <everest/test/bdd.h>
#include <everest/types/int32/all_traits.h>
#include <everest/mutable_crdt/counters/mutable_gacounter.h>

namespace everest {

void MutableGACounterSpecification() {
  Describe("A MutableGACounter type", []() {
    Describe("with an instance A of value 2 and an instance B of value 3", []() {
      auto aCounter = MutableGACounter<int, int>(1, 2);
      auto bCounter = MutableGACounter<int, int>(2, 3);
      Describe("and we Add() B to A", [&]() {
        It("should return a counter with the value of 5", [&]() {
          AssertEquals(5, aCounter.Add(bCounter).Value());
        });
        It("should not modify the value of A", [&]() {
          AssertEquals(2, aCounter.Value());
        });
      });
      Describe("and we Add() A to B", [&]() {
        It("should return a counter with the value of 5", [&]() {
          AssertEquals(5, bCounter.Add(aCounter).Value());
        });
        It("should not modify the value of B", [&]() {
          AssertEquals(3, bCounter.Value());
        });
      });
      Describe("and we call AddInPlace() for A to B", [&]() {
        It("should take on the max value when added with another counter", [&]() {
          AssertEquals(5, bCounter.AddInPlace(aCounter).Value());
        });
        It("should not modify the value of A", [&]() {
          AssertEquals(2, aCounter.Value());
        });
      });
      Describe("and we call AddInPlace() for B to A", [&]() {
        It("should take on the max value when added with another counter", [&]() {
          AssertEquals(5, aCounter.AddInPlace(bCounter).Value());
        });
      });
      Describe("and we call AddInPlace() on A with a lower A counter", [&]() {
        It("should not have any effect on A", [&]() {
          AssertEquals(5, aCounter.AddInPlace(MutableGACounter<int, int>(1, 2)).Value());
        });
      });
      Describe("and we call Equals() on it with an equivalent counter", [&]() {
        It("should return true for an equivalent counter", [&]() {
          AssertEquals(aCounter, bCounter);
        });
      });
      Describe("and we call Equals() on it with a non matching counter", [&]() {
        It("should return false for a non matching counter", [&]() {
          AssertNotEquals(aCounter, bCounter.Increment());
        });
      });
      Describe("and we call Increment() on it", [&]() {
        It("should increment the counter by one", [&]() {
          AssertEquals(6, aCounter.Increment().Value());
        });
      });
      Describe("and we call IncrementBy() on it with the value of 3", [&]() {
        It("should increment the counter by 3", [&]() {
          AssertEquals(9, aCounter.IncrementBy(3).Value());
        });
      });
      Describe("and we call Show() on instance A", [&]() {
        It("should correctly render the counter as a string", [&]() {
          AssertEquals(String("MutableGACounter(9)"), Show(aCounter));
        });
      });
    });
  });
}

}