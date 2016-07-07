#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Eq<MutableString> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableString& lhs, const MutableString& rhs) noexcept {
    if (Length(lhs) != Length(rhs) || Occupied(lhs) != Occupied(rhs)) {
      return false;
    } else {
      return memcmp(Pointer(lhs), Pointer(rhs), Occupied(lhs)) == 0;
    }
  }

};

}