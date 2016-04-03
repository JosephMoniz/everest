#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class Eq<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MaxMonoid<T>& lhs, const MaxMonoid<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

}