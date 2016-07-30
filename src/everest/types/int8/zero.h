#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Int8;

template <>
class ZeroVal<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Zero() noexcept {
    return Int8::Zero();
  }

};

}