#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class UInt16;

template <>
class Modulus<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Modulo(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}