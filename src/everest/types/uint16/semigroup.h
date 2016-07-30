#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class UInt16;

template <>
class Semigroup<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Add(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}