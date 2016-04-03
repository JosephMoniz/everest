#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class ZeroVal<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedMutableArray<T, S> Zero() noexcept {
    return MakeSharedMutableArray<T, S>({});
  }

};

}
