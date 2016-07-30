#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class Int8;

template <>
class OneVal<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 One() noexcept {
    return Int8::One();
  }

};

}