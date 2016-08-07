#pragma once

#include <everest/test/bdd.h>
#include <everest/monoids/max_monoid.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void MaxMonoidSpecification() {
  Describe("A MaxMonoid", []() {
    It("should return true when passing a matching MaxMonoid to Equals()", []() {
      auto expected = true;
      auto result   = Equals(MaxMonoid<int>(42), MaxMonoid<int>(42));
      auto failure  = "Equals(MaxMonoid(42), MaxMonoid(42)) did not return true";
      AssertEquals(failure, expected, result);
    });
    It("should return false when passing a different MaxMonoid to Equals()", []() {
      auto expected = false;
      auto result   = Equals(MaxMonoid<int>(42), MaxMonoid<int>(6));
      auto failure  = "Equals(MaxMonoid(42), MaxMonoid(6))";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to true when comparing a matching MaxMonoid with ==", []() {
      auto expected = true;
      auto result   = MaxMonoid<int>(42) == MaxMonoid<int>(42);
      auto failure  = "MaxMonoid(42) == MaxMonoid(42) did not evaluate to true";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to false when comparing a different MaxMonoid with ==", []() {
      auto expected = false;
      auto result   = MaxMonoid<int>(42) == MaxMonoid<int>(6);
      auto failure  = "MaxMonoid(42) == MaxMonoid(6) did not evaluate to false";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to false when comparing a matching MaxMonoid with !=", []() {
      auto expected = false;
      auto result   = MaxMonoid<int>(42) != MaxMonoid<int>(42);
      auto failure  = "MaxMonoid(42) != MaxMonoid(42) did not evaluate to false";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to true when comparing a different MaxMonoid with !=", []() {
      auto expected = true;
      auto result   = MaxMonoid<int>(42) != MaxMonoid<int>(6);
      auto failure  = "MaxMonoid(42) != MaxMonoid(6) did not evaluate to true";
      AssertEquals(failure, expected, result);
    });
    It("should return EQUALS when passed to Compare() with a matching MaxMonoid", []() {
      auto expected = Ordering::EQUAL;
      auto result   = Compare(MaxMonoid<int>(42), MaxMonoid<int>(42));
      auto failure  = "Compare(MaxMonoid(42), MaxMonoid(42)) did not return EQUAL";
      AssertEquals(failure, expected, result);
    });
    It("should return LESS when passed to Compare() with a greater MaxMonoid", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(MaxMonoid<int>(6), MaxMonoid<int>(42));
      auto failure  = "Compare(MaxMonoid(6), MaxMonoid(42)) did not return LESS";
      AssertEquals(failure, expected, result);
    });
    It("should return Greater when passed to Compare() with a lesser MaxMonoid", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(MaxMonoid<int>(42), MaxMonoid<int>(6));
      auto failure  = "Compare(MaxMonoid(42), MaxMonoid(6)) did not return GREATER";
      AssertEquals(failure, expected, result);
    });
    It("should return the greater of the two when called with Max()", []() {
      auto expected = MaxMonoid<int>(42);
      auto result   = Max(MaxMonoid<int>(42), MaxMonoid<int>(6));
      auto failure  = "Max(MaxMonoid(42), MaxMonoid(6)) did not return MaxMonoid(42)";
      AssertEquals(failure, expected, result);
    });
    It("should return the lesser of the two when called with Min()", []() {
      auto expected = MaxMonoid<int>(6);
      auto result   = Min(MaxMonoid<int>(42), MaxMonoid<int>(6));
      auto failure  = "Min(MaxMonoid(42), MaxMonoid(6)) did not return MaxMonoid(6)";
      AssertEquals(failure, expected, result);
    });
    It("should return the greater of the two when added with another MaxMonoid", []() {
      auto expected = MaxMonoid<int>(42);
      auto result   = MaxMonoid<int>(42) + MaxMonoid<int>(6);
      auto failure  = "MaxMonoid(42) + MaxMonoid(6) did not return MaxMonoid(42)";
      AssertEquals(failure, expected, result);
    });
    It("should render the correct value when called with Show()", []() {
      auto expected = String("MaxMonoid(42)");
      auto result   = Show(MaxMonoid<int>(42));
      auto failure  = "Show(MaxMonoid(42)) did not return 'MaxMonoid(42)'";
      AssertEquals(failure, expected, result);
    });
    It("should return the smallest possible value when called with Zero()", []() {
      auto expected = MaxMonoid<int>(std::numeric_limits<int>::min());
      auto result   = Zero<MaxMonoid<int>>();
      auto failure  = "Zero() did not return 'MaxMonoid(MIN)'";
      AssertEquals(failure, expected, result);
    });
  });
};

}