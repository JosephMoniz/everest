#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

class Int64;

template <>
class OneVal<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 One() noexcept {
    return Int64::One();
  }

};

}