#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class UInt32;

template <>
class OneVal<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 One() noexcept {
    return UInt32::One();
  }

};

}