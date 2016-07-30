#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class Int8;

template <>
class Subtractable<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Subtract(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}