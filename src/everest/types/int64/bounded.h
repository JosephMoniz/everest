#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

class Int64;

template <>
class Bounded<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 MinValue() noexcept {
    return Int64::MinValue();
  }

  static Int64 MaxValue() noexcept {
    return Int64::MaxValue();
  }

};

}