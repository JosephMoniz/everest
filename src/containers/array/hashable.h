#ifndef TRAITOROUS_CONTAINERS_ARRAY_HASHABLE_H
#define TRAITOROUS_CONTAINERS_ARRAY_HASHABLE_H

#include "containers/array.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T, size_t S>
class Hashable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Array<T, S>& array) noexcept {
    Hashable<LocalArray<T, S>>::Hash(*array.pointer());
  }

};

}

#endif
