#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Int8;

template <>
class Ord<Int8> final {
public:

  static Ordering Compare(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Int8 Min(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Min(rhs);
  }

  static Int8 Max(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}