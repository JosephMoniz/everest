#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class UInt32;

template<>
class Copyable<UInt32> final {
public:

  static constexpr bool exists = true;

  static UInt32 Copy(const UInt32 n) noexcept {
    return n.Copy();
  }

};

}