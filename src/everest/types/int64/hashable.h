#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Int64;

template<>
class Hashable<Int64> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Int64 hashable) noexcept {
    return hashable.Hash();
  }

};

}