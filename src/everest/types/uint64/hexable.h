#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class UInt64;

template<>
class Hexable<UInt64> final {
public:

  static constexpr bool exists = true;

  static String ToHex(UInt64 value) noexcept {
    return value.ToHex();
  }

};

}