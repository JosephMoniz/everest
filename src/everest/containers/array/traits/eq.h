#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Eq<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    auto lhsPointer = lhs.Pointer();
    auto rhsPointer = rhs.Pointer();
    for (size_t i = 0; i < S; i++) {
      if (lhsPointer[i] != rhsPointer[i]) {
        return false;
      }
    }
    return true;
  }

  template<size_t Rs>
  static bool Equals(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
