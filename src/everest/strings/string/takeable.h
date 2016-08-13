#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/strings/mutable_string/takeable.h>

namespace everest {

class String;

template<>
class Takeable<String> final {
public:

  static constexpr bool exists = true;

  static String Take(size_t size, const String& inString) noexcept {
    return inString.Take(size);
  }

  static String Take(size_t size, String&& inString) noexcept {
    return String(Takeable<MutableString>::Take(size, std::move(inString._wrapped)));
  }

  static String TakeWhile(Predicate<char> predicate, const String& string) noexcept {
    return string.TakeWhile(predicate);
  }

};

}