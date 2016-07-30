#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class UInt64;

template <>
class Shows<UInt64> final {
public:

  static constexpr bool exists = true;

  static String Show(UInt64 number) noexcept {
    return number.Show();
  }

};

}