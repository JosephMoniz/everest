#ifndef TRAITOROUS_STRING_SPEC_H
#define TRAITOROUS_STRING_SPEC_H

#include <string>

#include "test/bdd.h"
#include "types/string.h"

namespace traitorous {

void string_specification() {
  describe("A type string", []() {
    /*
    it("should return the length of the string when passed through length()", []() {
      return length(std::string("abc")) == 3;
    });
    it("should return true when an empty string is passed through is_empty()", []() {
      return is_empty(std::string(""));
    });
    it("should return false when a non empty string is passed through is_empty()", []() {
      return !is_empty(std::string("abc"));
    });
    it("should return true when an equiv string is passed through equals()", []() {
      return equals(std::string("abc"), std::string("abc"));
    });
    it("should return false when a different string is passed through equals()", []() {
      return !equals(std::string("abc"), std::string("def"));
    });
    it("should have a zero value of empty string", []() {
      return zero<std::string>() == std::string("");
    });
    it("should be addable via the add() function", []() {
      return add(std::string("abc"), std::string("def")) == std::string("abcdef");
    });
    it("should return LESS when a greater string is passed through cmp()", []() {
      return cmp(std::string("a"), std::string("b")) == LESS;
    });
    it("should return EQUAL when an equal string is passed through cmp()", []() {
      return cmp(std::string("a"), std::string("a")) == EQUAL;
    });
    it("should return GREATER when a greater string is passed through cmp()", []() {
      return cmp(std::string("b"), std::string("a")) == GREATER;
    });
    it("should return itself when a greater value is passed through min()", []() {
      return min(std::string("a"), std::string("b")) == std::string("a");
    });
    it("should return the other value when a lesser value is passed through min()", []() {
      return min(std::string("b"), std::string("a")) == std::string("a");
    });
    it("should return itself when a lesser value is passed though max()", []() {
      return max(std::string("b"), std::string("a")) == std::string("b");
    });
    it("should return the other value when a greater value is passed through max()", []() {
      return max(std::string("a"), std::string("b")) == std::string("b");
    });
    it("should return itself when passed through show()", []() {
      return show(std::string("abc")) == std::string("abc");
    });
     */
  });
}

}

#endif