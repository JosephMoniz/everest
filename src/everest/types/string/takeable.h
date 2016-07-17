#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/types/mutable/string/takeable.h>

namespace everest {

class String;

template<>
class Takeable<String> final {
public:

  static constexpr bool exists = true;

  static String Take(size_t size, const String& inString) noexcept {
    return String(Takeable<MutableString>::Take(size, inString._wrapped));
  }

  static String Take(size_t size, String&& inString) noexcept {
    return String(Takeable<MutableString>::Take(size, std::move(inString._wrapped)));
  }

  static String TakeWhile(Predicate<char> predicate, const String& string) noexcept {
    return String(Takeable<MutableString>::TakeWhile(predicate, string._wrapped));
  }

};

}