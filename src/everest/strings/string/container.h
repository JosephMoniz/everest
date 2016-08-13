#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

class String;

template <>
class Container<String> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const String& string) noexcept {
    return string.Length();
  }

  static bool IsEmpty(const String& string) noexcept {
    return string.IsEmpty();
  }

};

}