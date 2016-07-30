#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class UInt16;

template <>
class Bounded<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 MinValue() noexcept {
    return UInt16::MinValue();
  }

  static UInt16 MaxValue() noexcept {
    return UInt16::MaxValue();
  }

};

}