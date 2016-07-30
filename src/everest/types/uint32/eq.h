#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class UInt32;

template <>
class Eq<UInt32> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(UInt32 lhs, UInt32 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<UInt32> Equals(UInt32 lhs) noexcept {
  return [=](UInt32 rhs) {
    return lhs.Equals(rhs);
  };
}

}