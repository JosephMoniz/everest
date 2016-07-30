#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Int64;

template <>
class ZeroVal<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Zero() noexcept {
    return Int64::Zero();
  }

};

}