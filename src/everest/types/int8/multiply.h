#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class Int8;

template <>
class Multipliable<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Multiply(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}