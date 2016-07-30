#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class UInt32;

template <>
class Bounded<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 MinValue() noexcept {
    return UInt32::MinValue();
  }

  static UInt32 MaxValue() noexcept {
    return UInt32::MaxValue();
  }

};

}