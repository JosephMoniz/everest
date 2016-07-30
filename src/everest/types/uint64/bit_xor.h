#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class UInt64;

template <>
class BitXor<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 BinaryXor(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}