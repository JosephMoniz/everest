#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Int8;

template<>
class Copyable<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Copy(const Int8 n) noexcept {
    return n.Copy();
  }

};

}