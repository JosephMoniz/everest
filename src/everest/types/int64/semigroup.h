#pragma once

#include <everest/types/int64.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class Int64;

template <>
class Semigroup<Int64> final {
public:

  static constexpr bool exists = true;

  static Int64 Add(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}