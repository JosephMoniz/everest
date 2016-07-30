#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class Size;

template <>
class BitOr<Size> final {
public:

  static constexpr bool exists = true;

  static Size BinaryOr(const Size lhs, const Size rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}