#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_CONTAINER_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_CONTAINER_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template <class T, size_t S>
class Container<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const LocalArray<T, S>& o) noexcept {
    return (size_t) S;
  }

  static constexpr bool IsEmpty(const LocalArray<T, S>& o) noexcept {
    return S == 0;
  }

};

}

#endif
