#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class Size;

template <>
class BitAnd<Size> final {
public:

  static constexpr bool exists = true;

  static Size BinaryAnd(const Size lhs, const Size rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}