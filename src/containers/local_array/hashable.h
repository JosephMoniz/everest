#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_HASHABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_HASHABLE_H

#include "containers/array.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template <class T, size_t S>
class Hashable<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const LocalArray<T, S>& array) noexcept {
    int result = 37;
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hash(array.Pointer()[i]);
    }
    return result;
  }

};

}

#endif
