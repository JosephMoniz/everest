#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Size;

template <>
class Eq<Size> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Size lhs, const Size rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(Size lhs, Size rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<Size> Equals(Size lhs) noexcept {
  return [=](Size rhs) {
    return lhs.Equals(rhs);
  };
}

}