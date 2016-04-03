#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class ZeroVal<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedArray<T, S> Zero() noexcept {
    return MakeSharedArray<T, S>({});
  }

};

}
