#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class Int16;

template <>
class OneVal<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 One() noexcept {
    return Int16::One();
  }

};

}