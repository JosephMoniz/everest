#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class Int64;

template <>
class Multipliable<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Multiply(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}