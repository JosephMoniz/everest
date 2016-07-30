#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Int32;

template <>
class Ord<Int32> final {
public:

  static Ordering Compare(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Int32 Min(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static Int32 Max(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}