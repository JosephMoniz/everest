#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Int16;

template <>
class Eq<Int16> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Int16 lhs, const Int16 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(Int16 lhs, Int16 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<Int16> Equals(Int16 lhs) noexcept {
  return [=](Int16 rhs) {
    return lhs.Equals(rhs);
  };
}

}