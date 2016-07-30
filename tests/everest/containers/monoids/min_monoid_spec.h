#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>

namespace everest {

void MinMonoidSpecification() {
  Describe("A MinMonoid", []() {
    It("should return true when passing a matching MinMonoid to Equals()", []() {
      auto expected = true;
      auto result   = Equals(MinMonoid<int>(42), MinMonoid<int>(42));
      auto failure  = "Equals(MinMonoid(42), MinMonoid(42)) did not return true";
      AssertEquals(failure, expected, result);
    });
    It("should return false when passing a different MinMonoid to Equals()", []() {
      auto expected = false;
      auto result   = Equals(MinMonoid<int>(42), MinMonoid<int>(6));
      auto failure  = "Equals(MinMonoid(42), MinMonoid(6))";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to true when comparing a matching MinMonoid with ==", []() {
      auto expected = true;
      auto result   = MinMonoid<int>(42) == MinMonoid<int>(42);
      auto failure  = "MinMonoid(42) == MinMonoid(42) did not evaluate to true";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to false when comparing a different MinMonoid with ==", []() {
      auto expected = false;
      auto result   = MinMonoid<int>(42) == MinMonoid<int>(6);
      auto failure  = "MinMonoid(42) == MinMonoid(6) did not evaluate to false";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to false when comparing a matching MinMonoid with !=", []() {
      auto expected = false;
      auto result   = MinMonoid<int>(42) != MinMonoid<int>(42);
      auto failure  = "MinMonoid(42) != MinMonoid(42) did not evaluate to false";
      AssertEquals(failure, expected, result);
    });
    It("should evaluate to true when comparing a different MinMonoid with !=", []() {
      auto expected = true;
      auto result   = MinMonoid<int>(42) != MinMonoid<int>(6);
      auto failure  = "MinMonoid(42) != MinMonoid(6) did not evaluate to true";
      AssertEquals(failure, expected, result);
    });
    It("should return EQUALS when passed to Compare() with a matching MinMonoid", []() {
      auto expected = Ordering::EQUAL;
      auto result   = Compare(MinMonoid<int>(42), MinMonoid<int>(42));
      auto failure  = "Compare(MinMonoid(42), MinMonoid(42)) did not return EQUAL";
      AssertEquals(failure, expected, result);
    });
    It("should return LESS when passed to Compare() with a greater MinMonoid", []() {
      auto expected = Ordering::LESS;
      auto result   = Compare(MinMonoid<int>(6), MinMonoid<int>(42));
      auto failure  = "Compare(MinMonoid(6), MinMonoid(42)) did not return LESS";
      AssertEquals(failure, expected, result);
    });
    It("should return Greater when passed to Compare() with a lesser MinMonoid", []() {
      auto expected = Ordering::GREATER;
      auto result   = Compare(MinMonoid<int>(42), MinMonoid<int>(6));
      auto failure  = "Compare(MinMonoid(42), MinMonoid(6)) did not return GREATER";
      AssertEquals(failure, expected, result);
    });
    It("should return the greater of the two when called with Max()", []() {
      auto expected = MinMonoid<int>(42);
      auto result   = Max(MinMonoid<int>(42), MinMonoid<int>(6));
      auto failure  = "Max(MinMonoid(42), MinMonoid(6)) did not return MinMonoid(42)";
      AssertEquals(failure, expected, result);
    });
    It("should return the lesser of the two when called with Min()", []() {
      auto expected = MinMonoid<int>(6);
      auto result   = Min(MinMonoid<int>(42), MinMonoid<int>(6));
      auto failure  = "Min(MinMonoid(42), MinMonoid(6)) did not return MinMonoid(6)";
      AssertEquals(failure, expected, result);
    });
    It("should return the greater of the two when added with another MinMonoid", []() {
      auto expected = MinMonoid<int>(6);
      auto result   = MinMonoid<int>(42) + MinMonoid<int>(6);
      auto failure  = "MinMonoid(42) + MinMonoid(6) did not return MinMonoid(6)";
      AssertEquals(failure, expected, result);
    });
    It("should render the correct value when called with Show()", []() {
      auto expected = String("MinMonoid(42)");
      auto result   = Show(MinMonoid<int>(42));
      auto failure  = "Show(MinMonoid(42)) did not return 'MinMonoid(42)'";
      AssertEquals(failure, expected, result);
    });
    It("should return the smallest possible value when called with Zero()", []() {
      auto expected = MinMonoid<int>(std::numeric_limits<int>::max());
      auto result   = Zero<MinMonoid<int>>();
      auto failure  = "Zero() did not return 'MinMonoid(MAX)'";
      AssertEquals(failure, expected, result);
    });
  });
};

}