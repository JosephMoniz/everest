#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class UInt16;

template <>
class Shows<UInt16> final {
public:

  static constexpr bool exists = true;

  static String Show(UInt16 number) noexcept {
    return number.Show();
  }

};

}