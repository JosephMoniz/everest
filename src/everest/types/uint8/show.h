#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class UInt8;

template <>
class Shows<UInt8> final {
public:

  static constexpr bool exists = true;

  static String Show(UInt8 number) noexcept {
    return number.Show();
  }

};

}