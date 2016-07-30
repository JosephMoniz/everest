#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class UInt8;

template <>
class ZeroVal<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Zero() noexcept {
    return UInt8::Zero();
  }

};

}