#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Size;

template<>
class Hashable<Size> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Size hashable) noexcept {
    return hashable.Hash();
  }

};

}