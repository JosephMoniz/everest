#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class Size;

template <>
class BitXor<Size> final {
public:

  static constexpr bool exists = true;

  static Size BinaryXor(const Size lhs, const Size rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}