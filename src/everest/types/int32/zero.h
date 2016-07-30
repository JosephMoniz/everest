#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Int32;

template <>
class ZeroVal<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Zero() noexcept {
    return Int32::Zero();
  }

};

}