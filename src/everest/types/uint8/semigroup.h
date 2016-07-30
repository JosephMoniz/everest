#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class UInt8;

template <>
class Semigroup<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Add(const UInt8 lhs, const UInt8 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}