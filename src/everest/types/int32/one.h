#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class Int32;

template <>
class OneVal<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 One() noexcept {
    return Int32::One();
  }

};

}