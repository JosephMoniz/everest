#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class UInt32;

template <>
class BitAnd<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 BinaryAnd(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}