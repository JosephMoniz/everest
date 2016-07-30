#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class Int8;

template <>
class Dividable<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Divide(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}