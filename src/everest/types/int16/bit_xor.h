#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class Int16;

template <>
class BitXor<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 BinaryXor(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}