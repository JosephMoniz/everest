#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_ZERO_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_ZERO_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template<class T, size_t S>
class ZeroVal<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalArray<T, S> Zero() noexcept {
    return LocalArray<T, S>({});
  }

};

}

#endif
