#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class Int8;

template <>
class BitAnd<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 BinaryAnd(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}