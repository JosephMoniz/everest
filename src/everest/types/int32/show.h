#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class Int32;

template <>
class Shows<Int32> final {
public:

  static constexpr bool exists = true;

  static String Show(Int32 number) noexcept {
    return number.Show();
  }

};

}