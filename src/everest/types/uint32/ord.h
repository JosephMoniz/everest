#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class UInt32;

template <>
class Ord<UInt32> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static UInt32 Min(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static UInt32 Max(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}