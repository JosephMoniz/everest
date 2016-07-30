#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class Int8;

template <>
class Bounded<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 MinValue() noexcept {
    return Int8::MinValue();
  }

  static Int8 MaxValue() noexcept {
    return Int8::MaxValue();
  }

};

}