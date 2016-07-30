#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Int64;

template <>
class Eq<Int64> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Int64 lhs, const Int64 rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

bool Equals(Int64 lhs, Int64 rhs) noexcept {
  return lhs.Equals(rhs);
}

Predicate<Int64> Equals(Int64 lhs) noexcept {
  return [=](Int64 rhs) {
    return lhs.Equals(rhs);
  };
}

}