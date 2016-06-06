#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Ord<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Vector<T> &lhs, const Vector<T> &rhs) noexcept {
    return Ord<MutableVector<T>>::Compare(lhs._wrapped, rhs._wrapped);
  }

  static constexpr const Vector<T>& Min(const Vector<T> &lhs,
                                        const Vector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Vector<T>& Max(const Vector<T> &lhs,
                                        const Vector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}