#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/square_root.h>

namespace everest {

class Int64;

template <>
class SquareRoot<Int64> final {
public:

  static constexpr bool exists = true;

  static double Sqrt(const Int64 number) noexcept {
    return number.Sqrt();
  }

};

}