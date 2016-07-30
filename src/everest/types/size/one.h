#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class Size;

template <>
class OneVal<Size> final {
public:

  static constexpr bool exists = true;

  static Size One() noexcept {
    return Size::One();
  }

};

}