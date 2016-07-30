#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class UInt16;

template <>
class ZeroVal<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Zero() noexcept {
    return UInt16::Zero();
  }

};

}