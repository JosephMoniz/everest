#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MaxMonoid;

template<class T>
class Ord<MaxMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MaxMonoid<T> &lhs, const MaxMonoid<T> &rhs) noexcept {
    return Ord<T>::Compare(lhs.Value(), rhs.Value());
  }

  static const MaxMonoid<T>& Min(const MaxMonoid<T> &lhs, const MaxMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static const MaxMonoid<T>& Max(const MaxMonoid<T> &lhs, const MaxMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}