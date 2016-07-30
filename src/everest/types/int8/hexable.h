#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Int8;

template<>
class Hexable<Int8> final {
public:

  static constexpr bool exists = true;

  static String ToHex(Int8 value) noexcept {
    return value.ToHex();
  }

};

}