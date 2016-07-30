#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/square_root.h>

namespace everest {

class Int8;

template <>
class SquareRoot<Int8> final {
public:

  static constexpr bool exists = true;

  static double Sqrt(const Int8 number) noexcept {
    return number.Sqrt();
  }

};

}