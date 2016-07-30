#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

class Int8;

template <>
class Negation<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Negate(const Int8 n) noexcept {
    return n.Negate();
  }

};

}