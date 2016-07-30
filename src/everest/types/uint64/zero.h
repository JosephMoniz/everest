#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class UInt64;

template <>
class ZeroVal<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Zero() noexcept {
    return UInt64::Zero();
  }

};

}