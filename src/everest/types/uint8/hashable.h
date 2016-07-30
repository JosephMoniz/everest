#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class UInt8;

template<>
class Hashable<UInt8> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const UInt8 hashable) noexcept {
    return hashable.Hash();
  }

};

}