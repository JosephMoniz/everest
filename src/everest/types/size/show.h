#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class Size;

template <>
class Shows<Size> final {
public:

  static constexpr bool exists = true;

  static String Show(Size number) noexcept {
    return number.Show();
  }

};

}