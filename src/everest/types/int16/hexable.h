#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Int16;

template<>
class Hexable<Int16> final {
public:

  static constexpr bool exists = true;

  static String ToHex(Int16 value) noexcept {
    return value.ToHex();
  }

};

}