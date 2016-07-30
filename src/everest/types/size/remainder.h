#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class Size;

template <>
class Modulus<Size> final {
public:

  static constexpr bool exists = true;

  static Size Modulo(const Size lhs, const Size rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}