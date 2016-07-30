#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class UInt8;

template <>
class BitXor<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 BinaryXor(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}