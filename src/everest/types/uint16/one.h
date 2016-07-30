#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class UInt16;

template <>
class OneVal<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 One() noexcept {
    return UInt16::One();
  }

};

}