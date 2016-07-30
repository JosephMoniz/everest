#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/remainder.h>

namespace everest {

class Int64;

template <>
class Modulus<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Modulo(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Modulo(rhs);
  }

};

}