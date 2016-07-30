#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class UInt8;

template <>
class Bounded<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 MinValue() noexcept {
    return UInt8::MinValue();
  }

  static UInt8 MaxValue() noexcept {
    return UInt8::MaxValue();
  }

};

}