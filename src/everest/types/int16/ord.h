#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Int16;

template <>
class Ord<Int16> final {
public:

  static Ordering Compare(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Int16 Min(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static Int16 Max(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}