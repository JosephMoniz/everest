#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class UInt8;

template <>
class OneVal<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 One() noexcept {
    return UInt8::One();
  }

};

}