#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Ord<MutableTuple<T, U>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableTuple<T, U> &lhs, const MutableTuple<T, U> &rhs) noexcept {
    switch (Ord<T>::Compare(lhs._first, rhs._first)) {
      case Ordering::LESS:    return Ordering::LESS;
      case Ordering::GREATER: return Ordering::GREATER;
      case Ordering::EQUAL:   return Ord<U>::Compare(lhs._second, rhs._second);
    }
  }

  static constexpr const MutableTuple<T, U>& Min(const MutableTuple<T, U> &lhs,
                                                 const MutableTuple<T, U> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const MutableTuple<T, U>& Max(const MutableTuple<T, U> &lhs,
                                                 const MutableTuple<T, U> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}