#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class UInt64;

template <>
class Eq<UInt64> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(UInt64 lhs, UInt64 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<UInt64> Equals(UInt64 lhs) noexcept {
  return [=](UInt64 rhs) {
    return lhs.Equals(rhs);
  };
}

}