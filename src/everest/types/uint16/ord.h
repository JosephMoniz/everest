#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class UInt16;

template <>
class Ord<UInt16> final {
public:

  static Ordering Compare(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static UInt16 Min(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static UInt16 Max(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}