#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

class Int16;

template <>
class Negation<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Negate(const Int16 n) noexcept {
    return n.Negate();
  }

};

}