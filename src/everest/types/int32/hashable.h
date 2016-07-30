#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Int32;

template<>
class Hashable<Int32> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Int32 hashable) noexcept {
    return hashable.Hash();
  }

};

}