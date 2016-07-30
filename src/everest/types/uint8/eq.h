#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class UInt8;

template <>
class Eq<UInt8> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(UInt8 lhs, UInt8 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<UInt8> Equals(UInt8 lhs) noexcept {
  return [=](UInt8 rhs) {
    return lhs.Equals(rhs);
  };
}

}