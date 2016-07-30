#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class Int16;

template <>
class Subtractable<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Subtract(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}