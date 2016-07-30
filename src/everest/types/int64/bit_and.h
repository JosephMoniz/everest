#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/bit_and.h>

namespace everest {

class Int64;

template <>
class BitAnd<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 BinaryAnd(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.BinaryAnd(rhs);
  }

};

}