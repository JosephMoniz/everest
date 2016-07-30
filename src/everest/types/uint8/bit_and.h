#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class UInt8;

template <>
class BitAnd<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 BinaryAnd(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}