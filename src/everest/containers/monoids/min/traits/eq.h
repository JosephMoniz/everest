#pragma once

#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class Eq<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MinMonoid<T>& lhs, const MinMonoid<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

}