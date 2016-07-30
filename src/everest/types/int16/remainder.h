#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class Int16;

template <>
class Modulus<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Modulo(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}