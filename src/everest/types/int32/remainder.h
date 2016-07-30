#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class Int32;

template <>
class Modulus<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Modulo(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}