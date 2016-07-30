#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Int16;

template<>
class Copyable<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Copy(const Int16 n) noexcept {
    return n.Copy();
  }

};

}