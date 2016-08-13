#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/storable.h>

namespace everest {

class String;

template <>
class Storable<String> final {
public:

  static constexpr bool exists = true;

  static size_t Capacity(const String& string) noexcept {
    return string.Capacity();
  }

  static size_t Occupied(const String& string) noexcept {
    return string.Occupied();
  }

};

}