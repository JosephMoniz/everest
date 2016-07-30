#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class UInt32;

template <>
class Modulus<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Modulo(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}