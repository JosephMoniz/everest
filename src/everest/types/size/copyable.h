#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Size;

template<>
class Copyable<Size> final {
public:

  static constexpr bool exists = true;

  static Size Copy(const Size n) noexcept {
    return n.Copy();
  }

};

}