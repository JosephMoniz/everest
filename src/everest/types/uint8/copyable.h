#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class UInt8;

template<>
class Copyable<UInt8> final {
public:

  static constexpr bool exists = true;

  static UInt8 Copy(const UInt8 n) noexcept {
    return n.Copy();
  }

};

}