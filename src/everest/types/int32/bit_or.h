#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class Int32;

template <>
class BitOr<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 BinaryOr(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}