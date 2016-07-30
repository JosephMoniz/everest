#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/bit_xor.h>

namespace everest {

class Int64;

template <>
class BitXor<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 BinaryXor(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.BinaryXor(rhs);
  }

};

}