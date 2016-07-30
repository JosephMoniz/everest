#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Int64;

template<>
class Copyable<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Copy(const Int64 n) noexcept {
    return n.Copy();
  }

};

}