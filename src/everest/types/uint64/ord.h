#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class UInt64;

template <>
class Ord<UInt64> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static UInt64 Min(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static UInt64 Max(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}