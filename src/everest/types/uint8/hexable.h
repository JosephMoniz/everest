#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class UInt8;

template<>
class Hexable<UInt8> final {
public:

  static constexpr bool exists = true;

  static String ToHex(UInt8 value) noexcept {
    return value.ToHex();
  }

};

}