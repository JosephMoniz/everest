#pragma once

#include <string>

#include "everest/test/bdd.h"
#include "everest/strings/string.h"

namespace everest {

void StringSpecification() {
  Describe("A type mutable_string", []() {
    /*
    it("should return the length of the mutable_string when passed through Length()", []() {
      return Length(std::mutable_string("abc")) == 3;
    });
    it("should return true when an empty mutable_string is passed through IsEmpty()", []() {
      return IsEmpty(std::mutable_string(""));
    });
    it("should return false when a non empty mutable_string is passed through IsEmpty()", []() {
      return !IsEmpty(std::mutable_string("abc"));
    });
    it("should return true when an equiv mutable_string is passed through Equals()", []() {
      return Equals(std::mutable_string("abc"), std::mutable_string("abc"));
    });
    it("should return false when a different mutable_string is passed through Equals()", []() {
      return !Equals(std::mutable_string("abc"), std::mutable_string("def"));
    });
    it("should have a zero value of empty mutable_string", []() {
      return Zero<std::mutable_string>() == std::mutable_string("");
    });
    it("should be addable via the Add() function", []() {
      return Add(std::mutable_string("abc"), std::mutable_string("def")) == std::mutable_string("abcdef");
    });
    it("should return LESS when a greater mutable_string is passed through Compare()", []() {
      return Compare(std::mutable_string("a"), std::mutable_string("b")) == LESS;
    });
    it("should return EQUAL when an equal mutable_string is passed through Compare()", []() {
      return Compare(std::mutable_string("a"), std::mutable_string("a")) == EQUAL;
    });
    it("should return GREATER when a greater mutable_string is passed through Compare()", []() {
      return Compare(std::mutable_string("b"), std::mutable_string("a")) == GREATER;
    });
    it("should return itself when a greater value is passed through Min()", []() {
      return Min(std::mutable_string("a"), std::mutable_string("b")) == std::mutable_string("a");
    });
    it("should return the other value when a lesser value is passed through Min()", []() {
      return Min(std::mutable_string("b"), std::mutable_string("a")) == std::mutable_string("a");
    });
    it("should return itself when a lesser value is passed though Max()", []() {
      return Max(std::mutable_string("b"), std::mutable_string("a")) == std::mutable_string("b");
    });
    it("should return the other value when a greater value is passed through Max()", []() {
      return Max(std::mutable_string("a"), std::mutable_string("b")) == std::mutable_string("b");
    });
    it("should return itself when passed through Show()", []() {
      return Show(std::mutable_string("abc")) == std::mutable_string("abc");
    });
     */
  });
}

}
