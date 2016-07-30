#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class UInt32;

template<>
class Hashable<UInt32> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const UInt32 hashable) noexcept {
    return hashable.Hash();
  }

};

}