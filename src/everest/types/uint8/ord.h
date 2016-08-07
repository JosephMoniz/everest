#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class UInt8;

template <>
class Ord<UInt8> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static UInt8 Min(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static UInt8 Max(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}