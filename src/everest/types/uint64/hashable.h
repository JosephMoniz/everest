#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class UInt64;

template<>
class Hashable<UInt64> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const UInt64 hashable) noexcept {
    return hashable.Hash();
  }

};

}