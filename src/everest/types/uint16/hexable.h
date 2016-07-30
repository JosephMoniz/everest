#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class UInt16;

template<>
class Hexable<UInt16> final {
public:

  static constexpr bool exists = true;

  static String ToHex(UInt16 value) noexcept {
    return value.ToHex();
  }

};

}