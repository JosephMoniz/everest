#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

class Int32;

template <>
class Negation<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Negate(const Int32 n) noexcept {
    return n.Negate();
  }

};

}