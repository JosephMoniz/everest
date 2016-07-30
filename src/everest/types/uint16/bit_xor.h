#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class UInt16;

template <>
class BitXor<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 BinaryXor(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}