#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Hashable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Array<T, S>& array) noexcept {
    int result   = 37;
    auto pointer = Pointer(array);
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hash(pointer[i]);
    }
    return result;
  }

};

}
