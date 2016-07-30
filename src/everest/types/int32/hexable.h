#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Int32;

template<>
class Hexable<Int32> final {
public:

  static constexpr bool exists = true;

  static String ToHex(Int32 value) noexcept {
    return value.ToHex();
  }

};

}