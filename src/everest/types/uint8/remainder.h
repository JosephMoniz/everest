#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class UInt8;

template <>
class Modulus<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Modulo(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}