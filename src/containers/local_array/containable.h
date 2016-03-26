#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_CONTAINABLE_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template <class T, size_t S>
class Containable<LocalArray<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const LocalArray<T, S>& array) noexcept {
    for (size_t i = 0; i < S; i++) {
      if (array.Pointer()[i] == n) {
        return true;
      }
    }
    return false;
  }

};

}

#endif
