#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Containable<MutableArray<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const MutableArray<T, S>& array) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (array.Pointer()[i] == n) {
        return true;
      }
    }
    return false;
  }

};

}