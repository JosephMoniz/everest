#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Int32;

template<>
class Copyable<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Copy(const Int32 n) noexcept {
    return n.Copy();
  }

};

}