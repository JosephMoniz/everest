#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Int8;

template<>
class Hashable<Int8> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Int8 hashable) noexcept {
    return hashable.Hash();
  }

};

}