#pragma once

#include <everest/types/size.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

class Size;

template <>
class Semigroup<Size> final {
public:

  static constexpr bool exists = true;

  static Size Add(const Size lhs, const Size rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}