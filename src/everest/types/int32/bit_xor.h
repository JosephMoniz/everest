#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class Int32;

template <>
class BitXor<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 BinaryXor(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}