#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class Int8;

template <>
class Modulus<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Modulo(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}