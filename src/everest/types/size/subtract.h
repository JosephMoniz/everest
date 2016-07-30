#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class Size;

template <>
class Subtractable<Size> final {
public:

  static constexpr bool exists = true;

  static Size Subtract(const Size lhs, const Size rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}