#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Int64;

template <>
class Ord<Int64> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Int64 Min(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static Int64 Max(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}