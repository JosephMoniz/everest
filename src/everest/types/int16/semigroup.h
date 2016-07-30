#pragma once

#include <everest/types/int16.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class Int16;

template <>
class Semigroup<Int16> final {
public:

  static constexpr bool exists = true;

  static Int16 Add(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}