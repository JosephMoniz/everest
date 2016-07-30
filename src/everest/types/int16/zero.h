#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Int16;

template <>
class ZeroVal<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Zero() noexcept {
    return Int16::Zero();
  }

};

}