#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/divide.h>

namespace everest {

class UInt64;

template <>
class Dividable<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Divide(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Divide(rhs);
  }

};

}