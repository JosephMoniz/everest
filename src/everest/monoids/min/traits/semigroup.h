#pragma once

#include <everest/monoids/min_monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MinMonoid;

template <class T>
class Semigroup<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static MinMonoid<T> Add(const MinMonoid<T>& lhs, const MinMonoid<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}