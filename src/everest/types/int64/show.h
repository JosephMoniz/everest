#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class Int64;

template <>
class Shows<Int64> final {
public:

  static constexpr bool exists = true;

  static String Show(Int64 number) noexcept {
    return number.Show();
  }

};

}