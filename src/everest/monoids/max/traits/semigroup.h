#pragma once

#include <everest/monoids/max_monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MaxMonoid;

template <class T>
class Semigroup<MaxMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static MaxMonoid<T> Add(const MaxMonoid<T>& lhs, const MaxMonoid<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}