#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class UInt64;

template <>
class BitAnd<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 BinaryAnd(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}