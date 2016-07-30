#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class UInt32;

template <>
class BitOr<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 BinaryOr(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}