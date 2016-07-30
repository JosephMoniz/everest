#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class Int32;

template <>
class Multipliable<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Multiply(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}