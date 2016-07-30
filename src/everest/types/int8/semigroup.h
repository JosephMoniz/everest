#pragma once

#include <everest/types/int8.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class Int8;

template <>
class Semigroup<Int8> final {
public:

  static constexpr bool exists = true;

  static Int8 Add(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}