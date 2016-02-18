#ifndef TRAITOROUS_CONTAINERS_ARRAY_ZERO_H
#define TRAITOROUS_CONTAINERS_ARRAY_ZERO_H

#include "containers/array.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template<class T, size_t S>
class ZeroVal<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr Array<T, S> Zero() noexcept {
    return MakeArray<T, S>({});
  }

};

}

#endif
