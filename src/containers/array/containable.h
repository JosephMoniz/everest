#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Containable<Array<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const Array<T, S>& array) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (array.Pointer()[i] == n) {
        return true;
      }
    }
    return false;
  }

};

}
