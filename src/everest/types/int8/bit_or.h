#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/bit_or.h>

namespace everest {

class Int8;

template <>
class BitOr<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 BinaryOr(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.BinaryOr(rhs);
  }

};

}