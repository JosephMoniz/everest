#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class UInt32;

template <>
class BitXor<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 BinaryXor(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}