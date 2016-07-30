#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class UInt16;

template <>
class BitOr<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 BinaryOr(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}