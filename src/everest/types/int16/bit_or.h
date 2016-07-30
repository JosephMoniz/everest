#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class Int16;

template <>
class BitOr<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 BinaryOr(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}