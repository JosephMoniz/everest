#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class UInt8;

template <>
class Dividable<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Divide(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}