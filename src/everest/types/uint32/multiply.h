#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class UInt32;

template <>
class Multipliable<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Multiply(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}