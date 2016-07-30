#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class UInt8;

template <>
class Multipliable<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Multiply(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}