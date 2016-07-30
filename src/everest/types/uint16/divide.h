#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class UInt16;

template <>
class Dividable<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Divide(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}