#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class Int16;

template <>
class Multipliable<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Multiply(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}