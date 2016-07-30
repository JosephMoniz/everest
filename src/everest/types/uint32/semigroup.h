#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class UInt32;

template <>
class Semigroup<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Add(const UInt32 lhs, const UInt32 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}