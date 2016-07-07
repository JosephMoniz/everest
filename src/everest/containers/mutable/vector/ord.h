#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Ord<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableVector<T> &lhs, const MutableVector<T> &rhs) noexcept {
    auto lhsLength = Length(lhs);
    auto rhsLength = Length(rhs);
    if (rhsLength == lhsLength) {
      auto lhsPointer = Pointer(lhs);
      auto rhsPointer = Pointer(rhs);
      for (size_t i = 0; i < lhsLength; i++) {
        switch (Ord<T>::Compare(lhsPointer[i], rhsPointer[i])) {
          case Ordering::LESS:    return Ordering::LESS;
          case Ordering::GREATER: return Ordering::GREATER;
          case Ordering::EQUAL:   continue;
        }
      }
      return Ordering::EQUAL;
    } else {
      if (lhsLength < rhsLength) {
        return Ordering::LESS;
      } else {
        return Ordering::GREATER;
      }
    }
  }

  static constexpr const MutableVector<T>& Min(const MutableVector<T> &lhs,
                                               const MutableVector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const MutableVector<T>& Max(const MutableVector<T> &lhs,
                                               const MutableVector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}