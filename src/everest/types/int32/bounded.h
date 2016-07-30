#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class Int32;

template <>
class Bounded<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 MinValue() noexcept {
    return Int32::MinValue();
  }

  static Int32 MaxValue() noexcept {
    return Int32::MaxValue();
  }

};

}