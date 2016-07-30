#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Size;

template <>
class ZeroVal<Size> final {
public:

  static constexpr bool exists = true;

  static Size Zero() noexcept {
    return Size::Zero();
  }

};

}