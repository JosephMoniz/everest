#pragma once

#include <everest/monoids/min_monoid.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MinMonoid;

template<class T>
class Ord<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MinMonoid<T> &lhs, const MinMonoid<T> &rhs) noexcept {
    return Ord<T>::Compare(lhs.Value(), rhs.Value());
  }

  static const MinMonoid<T>& Min(const MinMonoid<T> &lhs, const MinMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static const MinMonoid<T>& Max(const MinMonoid<T> &lhs, const MinMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}