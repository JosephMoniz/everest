#ifndef TRAITOROUS_CONTAINERS_ARRAY_CONTAINER_H
#define TRAITOROUS_CONTAINERS_ARRAY_CONTAINER_H

#include "containers/array.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template <class T, size_t S>
class Container<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Array<T, S>& o) noexcept {
    return Container<LocalArray<T, S>>::Length(*o.Pointer());
  }

  static constexpr bool IsEmpty(const Array<T, S>& o) noexcept {
    return Container<LocalArray<T, S>>::IsEmpty(*o.Pointer());
  }

};

}

#endif
