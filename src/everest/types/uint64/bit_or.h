#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class UInt64;

template <>
class BitOr<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 BinaryOr(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}