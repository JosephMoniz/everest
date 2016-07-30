#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

class Int64;

template <>
class Negation<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Negate(const Int64 n) noexcept {
    return n.Negate();
  }

};

}