#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class UInt64;

template <>
class Semigroup<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Add(const UInt64 lhs, const UInt64 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}