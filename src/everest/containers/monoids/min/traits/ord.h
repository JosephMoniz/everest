#pragma once

#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Ord<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const MinMonoid<T> &lhs,
                                    const MinMonoid<T> &rhs) noexcept
  {
    return Ord<T>::Compare(lhs.Value(), rhs.Value());
  }

  static constexpr const MinMonoid<T>& Min(const MinMonoid<T> &lhs,
                                           const MinMonoid<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const MinMonoid<T>& Max(const MinMonoid<T> &lhs,
                                           const MinMonoid<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}