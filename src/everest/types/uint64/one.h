#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class UInt64;

template <>
class OneVal<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 One() noexcept {
    return UInt64::One();
  }

};

}