#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class UInt64;

template <>
class Multipliable<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Multiply(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}