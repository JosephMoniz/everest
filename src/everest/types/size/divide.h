#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class Size;

template <>
class Dividable<Size> final {
public:

  static constexpr bool exists = true;

  static Size Divide(const Size lhs, const Size rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}