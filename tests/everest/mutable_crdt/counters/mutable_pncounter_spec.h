#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_crdt/counters/mutable_pncounter.h>

namespace everest {

void MutablePNCounterSpecification() {
  Describe("A MutablePNCounter type", []() {
    Describe("with an instance A of value 9 and an instance B of value -3", []() {
      auto aCounter = MutablePNCounter<int>(9);
      auto bCounter = MutablePNCounter<int>(-3);
      Describe("and we render A with show", [&]() {
        It("should correctly render as 9", [&]() {
          AssertEquals(String("MutablePNCounter(9)"), aCounter.Show());
        });
      });
      Describe("and we render B with show", [&]() {
        It("should correctly render as -3", [&]() {
          AssertEquals(String("MutablePNCounter(-3)"), bCounter.Show());
        });
      });
      Describe("and we pass A and B to Equals()", [&]() {
        It("should return false", [&]() {
          AssertFalse(aCounter.Equals(bCounter));
        });
      });
      Describe("and we pass A and an equivalent value to Equals()", [&]() {
        It("should return true", [&]() {
          AssertTrue(aCounter.Equals(MutablePNCounter<int>(-3).IncrementBy(12)));
        });
      });
      Describe("and we pass B and an equivalent value to Equals()", [&]() {
        It("should return true", [&]() {
          AssertTrue(bCounter.Equals(MutablePNCounter<int>(6).DecrementBy(9)));
        });
      });
      Describe("and we call Increment() on A", [&]() {
        It("should increment the value of A to 10", [&]() {
          AssertEquals(10, aCounter.Increment().Value());
        });
      });
      Describe("and we call Increment() on B", [&]() {
        It("should increment the value of B to -2", [&]() {
          AssertEquals(-2, bCounter.Increment().Value());
        });
      });
      Describe("and we call IncrementBy() on A with 2", [&]() {
        It("should increment the value of A to 12", [&]() {
          AssertEquals(12, aCounter.IncrementBy(2).Value());
        });
      });
      Describe("and we call IncrementBy() on B with 5", [&]() {
        It("should increment the value of B to 3", [&]() {
          AssertEquals(3, bCounter.IncrementBy(5).Value());
        });
      });
      Describe("and we call Decrement on A", [&]() {
        It("should decrement the value of A to 11", [&]() {
          AssertEquals(11, aCounter.Decrement().Value());
        });
      });
      Describe("and we call Decrement on B", [&]() {
        It("should decrement the value of B to 2", [&]() {
          AssertEquals(2, bCounter.Decrement().Value());
        });
      });
      Describe("and we call DecrementBy on A with 5", [&]() {
        It("should decrement the value of A to 6", [&]() {
          AssertEquals(6, aCounter.DecrementBy(5).Value());
        });
      });
      Describe("and we call DecrementBy on B with 8", [&]() {
        It("should decrement the value of B to -6", [&]() {
          AssertEquals(-6, bCounter.DecrementBy(8).Value());
        });
      });
      Describe("and we Add() A to B", [&]() {
        It("should return a counter of value 0", [&]() {
          AssertEquals(0, aCounter.Add(bCounter).Value());
        });
        It("should not modify A", [&]() {
          AssertEquals(6, aCounter.Value());
        });
      });
      Describe("and we Add() B to A", [&]() {
        It("should return a counter of value 0", [&]() {
          AssertEquals(0, bCounter.Add(aCounter).Value());
        });
        It("should not modify B", [&]() {
          AssertEquals(-6, bCounter.Value());
        });
      });
      Describe("and we AddInPlace() A to B", [&]() {
        It("should return set the value of A to 0", [&]() {
          AssertEquals(0, bCounter.AddInPlace(aCounter).Value());
          AssertEquals(0, bCounter.Value());
        });
      });
      Describe("and we AddInPlace() B to A", [&]() {
        It("should return set the value of B to 0", [&]() {
          AssertEquals(0, aCounter.AddInPlace(bCounter).Value());
          AssertEquals(0, aCounter.Value());
        });
      });
      Describe("and we call Show() on A", [&]() {
        It("should render the correct string", [&]() {
          AssertEquals(String("MutablePNCounter(0)"), aCounter.Show());
        });
      });
    });
  });
}

}