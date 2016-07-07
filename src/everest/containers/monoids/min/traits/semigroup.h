#pragma once

#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MinMonoid;

template <class T>
class Semigroup<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr MinMonoid<T> Add(const MinMonoid<T>& lhs,
                                    const MinMonoid<T>& rhs) noexcept
  {
    switch (Ord<T>::Compare(lhs.Value(), rhs.Value())) {
      case Ordering::LESS:    return lhs;
      case Ordering::GREATER: return rhs;
      case Ordering::EQUAL:   return lhs;
    }
  }

};

}