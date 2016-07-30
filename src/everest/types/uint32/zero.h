#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class UInt32;

template <>
class ZeroVal<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Zero() noexcept {
    return UInt32::Zero();
  }

};

}