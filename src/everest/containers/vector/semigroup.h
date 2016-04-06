#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class Semigroup<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Vector<T> Add(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    auto lhsLength   = lhs.Length();
    auto rhsLength   = rhs.Length();
    auto memory      = MutableMemory<T>(lhsLength + rhsLength);
    auto destPointer = memory.MutablePointer();
    auto lhsPointer  = lhs.Pointer();
    auto rhsPointer  = rhs.Pointer();
    for (size_t i = 0; i < lhsLength; i++) {
      destPointer[i] = lhsPointer[i];
    }
    for (size_t i = 0; i < rhsLength; i++) {
      destPointer[i + lhsLength] = rhsPointer[i];
    }
    return Vector<T>(Memory<T>(memory));
  }

};

}