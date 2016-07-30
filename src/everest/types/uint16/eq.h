#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class UInt16;

template <>
class Eq<UInt16> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(UInt16 lhs, UInt16 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<UInt16> Equals(UInt16 lhs) noexcept {
  return [=](UInt16 rhs) {
    return lhs.Equals(rhs);
  };
}

}