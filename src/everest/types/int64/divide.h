#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class Int64;

template <>
class Dividable<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Divide(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}