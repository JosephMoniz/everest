#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Int64;

template<>
class Hexable<Int64> final {
public:

  static constexpr bool exists = true;

  static String ToHex(Int64 value) noexcept {
    return value.ToHex();
  }

};

}