#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class ZeroVal<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableArray<T, S> Zero() noexcept {
    return MutableArray<T, S>({});
  }

};

}
