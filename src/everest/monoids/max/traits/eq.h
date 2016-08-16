#pragma once

#include <everest/monoids/max_monoid.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class MaxMonoid;

template<class T>
class Eq<MaxMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MaxMonoid<T>& lhs, const MaxMonoid<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}