#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Int32;

template <>
class Eq<Int32> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Int32 lhs, const Int32 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(Int32 lhs, Int32 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<Int32> Equals(Int32 lhs) noexcept {
  return [=](Int32 rhs) {
    return lhs.Equals(rhs);
  };
}

}