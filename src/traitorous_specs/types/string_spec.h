#ifndef TRAITOROUS_STRING_SPEC_H
#define TRAITOROUS_STRING_SPEC_H

#include <string>

#include "test/bdd.h"
#include "types/string.h"

namespace traitorous {

void string_specification() {
  describe("A type string", []() {
    /*
    it("should return the length of the string when passed through Length()", []() {
      return Length(std::string("abc")) == 3;
    });
    it("should return true when an empty string is passed through IsEmpty()", []() {
      return IsEmpty(std::string(""));
    });
    it("should return false when a non empty string is passed through IsEmpty()", []() {
      return !IsEmpty(std::string("abc"));
    });
    it("should return true when an equiv string is passed through Equals()", []() {
      return Equals(std::string("abc"), std::string("abc"));
    });
    it("should return false when a different string is passed through Equals()", []() {
      return !Equals(std::string("abc"), std::string("def"));
    });
    it("should have a zero value of empty string", []() {
      return Zero<std::string>() == std::string("");
    });
    it("should be addable via the Add() function", []() {
      return Add(std::string("abc"), std::string("def")) == std::string("abcdef");
    });
    it("should return LESS when a greater string is passed through Compare()", []() {
      return Compare(std::string("a"), std::string("b")) == LESS;
    });
    it("should return EQUAL when an equal string is passed through Compare()", []() {
      return Compare(std::string("a"), std::string("a")) == EQUAL;
    });
    it("should return GREATER when a greater string is passed through Compare()", []() {
      return Compare(std::string("b"), std::string("a")) == GREATER;
    });
    it("should return itself when a greater value is passed through Min()", []() {
      return Min(std::string("a"), std::string("b")) == std::string("a");
    });
    it("should return the other value when a lesser value is passed through Min()", []() {
      return Min(std::string("b"), std::string("a")) == std::string("a");
    });
    it("should return itself when a lesser value is passed though Max()", []() {
      return Max(std::string("b"), std::string("a")) == std::string("b");
    });
    it("should return the other value when a greater value is passed through Max()", []() {
      return Max(std::string("a"), std::string("b")) == std::string("b");
    });
    it("should return itself when passed through Show()", []() {
      return Show(std::string("abc")) == std::string("abc");
    });
     */
  });
}

}

#endif