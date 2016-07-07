#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Eq<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableArray<T, S>& lhs, const MutableArray<T, S>& rhs) noexcept {
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
  static bool Equals(const MutableArray<T, S>& lhs, const MutableArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
