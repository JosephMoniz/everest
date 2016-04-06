#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class Eq<Vector<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    auto leftLength = lhs.Length();
    if (leftLength == rhs.Length()) {
      auto lhsPointer = lhs.Pointer();
      auto rhsPointer = rhs.Pointer();
      for (size_t i = 0; i < leftLength; i++) {
        if (lhsPointer[i] != rhsPointer[i]) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

};

}