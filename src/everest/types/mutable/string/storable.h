#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/storable.h>

namespace everest {

class MutableString;

template <>
class Storable<MutableString> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Capacity(const MutableString& string) noexcept {
    return string.Capacity();
  }

  static constexpr size_t Occupied(const MutableString& string) noexcept {
    return string.Occupied();
  }

};

}