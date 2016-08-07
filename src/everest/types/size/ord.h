#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Size;

template <>
class Ord<Size> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Size lhs, const Size rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Size Min(const Size lhs, const Size rhs) noexcept {
    return lhs.Min(rhs);
  }

  static Size Max(const Size lhs, const Size rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}