#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

class UInt64;

template <>
class Subtractable<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Subtract(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}