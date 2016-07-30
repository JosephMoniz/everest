#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class Int32;

template <>
class Subtractable<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Subtract(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}