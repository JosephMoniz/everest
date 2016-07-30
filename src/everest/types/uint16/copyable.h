#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class UInt16;

template<>
class Copyable<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Copy(const UInt16 n) noexcept {
    return n.Copy();
  }

};

}