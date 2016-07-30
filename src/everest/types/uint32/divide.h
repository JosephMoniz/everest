#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class UInt32;

template <>
class Dividable<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Divide(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}