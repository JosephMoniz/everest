#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Int16;

template<>
class Hashable<Int16> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Int16 hashable) noexcept {
    return hashable.Hash();
  }

};

}