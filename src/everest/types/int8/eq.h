#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Int8;

template <>
class Eq<Int8> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Int8 lhs, const Int8 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(Int8 lhs, Int8 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<Int8> Equals(Int8 lhs) noexcept {
  return [=](Int8 rhs) {
    return lhs.Equals(rhs);
  };
}

}