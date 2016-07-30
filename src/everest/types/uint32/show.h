#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class UInt32;

template <>
class Shows<UInt32> final {
public:

  static constexpr bool exists = true;

  static String Show(UInt32 number) noexcept {
    return number.Show();
  }

};

}