#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/square_root.h>

namespace everest {

class Int32;

template <>
class SquareRoot<Int32> final {
public:

  static constexpr bool exists = true;

  static double Sqrt(const Int32 number) noexcept {
    return number.Sqrt();
  }

};

}