#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class UInt64;

template<>
class Copyable<UInt64> final {
public:

  static constexpr bool exists = true;

  static UInt64 Copy(const UInt64 n) noexcept {
    return n.Copy();
  }

};

}