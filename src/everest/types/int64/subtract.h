#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class Int64;

template <>
class Subtractable<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Subtract(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}