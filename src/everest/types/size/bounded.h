#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class Size;

template <>
class Bounded<Size> final {
public:

  static constexpr bool exists = true;

  static Size MinValue() noexcept {
    return Size::MinValue();
  }

  static Size MaxValue() noexcept {
    return Size::MaxValue();
  }

};

}