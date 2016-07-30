#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class UInt16;

template <>
class Subtractable<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Subtract(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}