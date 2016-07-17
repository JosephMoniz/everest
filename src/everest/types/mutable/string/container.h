#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

class MutableString;

template <>
class Container<MutableString> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableString& string) noexcept {
    return string.Length();
  }

  static constexpr bool IsEmpty(const MutableString& string) noexcept {
    return string.Length() == 0;
  }

};

}