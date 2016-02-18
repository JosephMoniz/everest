#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_EQ_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_EQ_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template<class T, size_t S>
class Eq<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const LocalArray<T, S>& lhs, const LocalArray<T, S>& rhs) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (lhs.pointer()[i] != rhs.pointer()[i]) {
        return false;
      }
    }
    return true;
  }

  template<size_t Rs>
  static bool Equals(const LocalArray<T, S>& lhs, const LocalArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}

#endif
