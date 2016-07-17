#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

class String;

template <>
class Container<String> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const String& string) noexcept {
    return string.Length();
  }

  static constexpr bool IsEmpty(const String& string) noexcept {
    return string.IsEmpty();
  }

};

}