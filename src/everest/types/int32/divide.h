#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class Int32;

template <>
class Dividable<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Divide(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}