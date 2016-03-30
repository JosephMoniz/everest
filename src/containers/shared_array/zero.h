#pragma once

#include "containers/array.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class ZeroVal<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedArray<T, S> Zero() noexcept {
    return MakeSharedArray<T, S>({});
  }

};

}
