#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class UInt8;

template <>
class BitOr<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 BinaryOr(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}