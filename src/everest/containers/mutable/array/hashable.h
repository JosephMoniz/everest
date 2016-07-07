#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Hashable<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableArray<T, S>& array) noexcept {
    int result   = 37;
    auto pointer = array.Pointer();
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hash(pointer[i]);
    }
    return result;
  }

};

}
