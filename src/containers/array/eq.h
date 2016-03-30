#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Eq<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (lhs.Pointer()[i] != rhs.Pointer()[i]) {
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
