#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class UInt64;

template <>
class Bounded<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 MinValue() noexcept {
    return UInt64::MinValue();
  }

  static UInt64 MaxValue() noexcept {
    return UInt64::MaxValue();
  }

};

}