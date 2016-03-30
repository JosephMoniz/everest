#pragma once

#include "containers/array.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Hashable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Array<T, S>& array) noexcept {
    int result = 37;
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hash(array.Pointer()[i]);
    }
    return result;
  }

};

}
