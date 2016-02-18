#ifndef TRAITOROUS_CONTAINERS_ARRAY_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_ARRAY_CONTAINABLE_H

#include "containers/array.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template <class T, size_t S>
class Containable<Array<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const Array<T, S>& array) noexcept {
    return Containable<LocalArray<T, S>, T>::Contains(n, *array.pointer());
  }

};

}

#endif
