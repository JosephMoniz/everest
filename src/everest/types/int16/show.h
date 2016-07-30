#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class Int16;

template <>
class Shows<Int16> final {
public:

  static constexpr bool exists = true;

  static String Show(Int16 number) noexcept {
    return number.Show();
  }

};

}