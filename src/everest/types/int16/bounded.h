#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class Int16;

template <>
class Bounded<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 MinValue() noexcept {
    return Int16::MinValue();
  }

  static Int16 MaxValue() noexcept {
    return Int16::MaxValue();
  }

};

}