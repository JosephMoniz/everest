#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class Int8;

template <>
class Shows<Int8> final {
public:

  static constexpr bool exists = true;

  static String Show(Int8 number) noexcept {
    return number.Show();
  }

};

}