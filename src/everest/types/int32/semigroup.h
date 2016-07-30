#pragma once

#include <everest/types/int32.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class Int32;

template <>
class Semigroup<Int32> final {
public:

  static constexpr bool exists = true;

  static Int32 Add(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}