#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Hashable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const SharedArray<T, S>& array) noexcept {
    Hashable<MutableArray<T, S>>::Hash(*array.Pointer());
  }

};

}
