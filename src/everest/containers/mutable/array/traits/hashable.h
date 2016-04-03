#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Hashable<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableArray<T, S>& array) noexcept {
    int result = 37;
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hash(array.Pointer()[i]);
    }
    return result;
  }

};

}
