#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Eq<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableArray<T, S>& lhs, const MutableArray<T, S>& rhs) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (lhs.Pointer()[i] != rhs.Pointer()[i]) {
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
