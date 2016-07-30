#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class UInt8;

template <>
class Subtractable<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Subtract(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}