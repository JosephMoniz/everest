#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Ord<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Vector<T> &lhs, const Vector<T> &rhs) noexcept {
    auto lhsLength = lhs.Length();
    auto rhsLength = rhs.Length();
    if (rhsLength == lhsLength) {
      auto lhsPointer = lhs.Pointer();
      auto rhsPointer = rhs.Pointer();
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