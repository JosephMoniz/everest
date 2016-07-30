#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class Size;

template <>
class Multipliable<Size> final {
public:

  static constexpr bool exists = true;

  static Size Multiply(const Size lhs, const Size rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}