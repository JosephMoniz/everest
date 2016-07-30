#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class UInt32;

template<>
class Hexable<UInt32> final {
public:

  static constexpr bool exists = true;

  static String ToHex(UInt32 value) noexcept {
    return value.ToHex();
  }

};

}