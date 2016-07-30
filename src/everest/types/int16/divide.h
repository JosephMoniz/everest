#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class Int16;

template <>
class Dividable<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Divide(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}