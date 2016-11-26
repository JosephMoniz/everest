#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_crdt/counters/mutable_gcounter.h>

namespace everest {

void MutableGCounterSpecification() {
  Describe("A MutableGCounter type", []() {
    Describe("and we create an instance with the empty constructor", []() {
      It("should return a counter signifying the zero value", []() {
        AssertEquals(0, MutableGCounter<int>::Zero().Value());
      });
    });
    Describe("and we call Zero() on it", []() {
      It("should return a counter signifying the zero value", []() {
        AssertEquals(0, MutableGCounter<int>::Zero().Value());
      });
    });
    Describe("with the value of 1", []() {
      auto counter = MutableGCounter<int>(1);
      Describe("and we call Show() on it", [&]() {
        It("should correctly render the counter as a string", [&]() {
          AssertEquals("MutableGCounter(1)", counter.Show());
        });
      });
      Describe("and we call Value() on it", [&]() {
        It("should correctly return the counters inner value", [&]() {
          AssertEquals(1, counter.Value());
        });
      });
      Describe("and we call Add() on it with counter of a greater value", [&]() {
        It("should return the max value when added with another counter", [&]() {
          AssertEquals(3, counter.Add(MutableGCounter<int>(3)).Value());
        });
      });
      Describe("and we call Add() on it with counter of a lesser value", [&]() {
        It("should return the max value when added with another counter", [&]() {
          AssertEquals(1, counter.Add(MutableGCounter<int>(0)).Value());
        });
      });
      Describe("and we call AddInPlace() on it with a counter of a greater value", [&]() {
        It("should take on the max value when added with another counter", [&]() {
          AssertEquals(3, counter.AddInPlace(MutableGCounter<int>(3)).Value());
        });
      });
      Describe("and we call AddInPlace() on it with a counter of a lesser value", [&]() {
        It("should take on the max value when added with another counter", [&]() {
          AssertEquals(3, counter.AddInPlace(MutableGCounter<int>(1)).Value());
        });
      });
      Describe("and we call Equals() on it with an equivalent counter", [&]() {
        It("should return true for an equivalent counter", [&]() {
          AssertTrue(counter.Equals(MutableGCounter<int>(3)));
        });
      });
      Describe("and we call Equals() on it with a non matching counter", [&]() {
        It("should return false for a non matching counter", [&]() {
          AssertFalse(counter.Equals(MutableGCounter<int>(6)));
        });
      });
      Describe("and we call Increment() on it", [&]() {
        It("should increment the counter by one", [&]() {
          AssertEquals(4, counter.Increment().Value());
        });
      });
      Describe("and we call IncrementBy() on it with the value of 3", [&]() {
        It("should increment the counter by 3", [&]() {
          AssertEquals(6, counter.IncrementBy(2).Value());
        });
      });
    });
  });
}

}