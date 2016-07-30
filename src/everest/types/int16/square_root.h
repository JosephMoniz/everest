#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/square_root.h>

namespace everest {

class Int16;

template <>
class SquareRoot<Int16> final {
public:

  static constexpr bool exists = true;

  static double Sqrt(const Int16 number) noexcept {
    return number.Sqrt();
  }

};

}