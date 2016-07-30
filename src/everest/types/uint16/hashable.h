#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class UInt16;

template<>
class Hashable<UInt16> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const UInt16 hashable) noexcept {
    return hashable.Hash();
  }

};

}