#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class UInt32;

template <>
class Subtractable<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Subtract(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}