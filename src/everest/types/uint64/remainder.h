#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class UInt64;

template <>
class Modulus<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Modulo(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}