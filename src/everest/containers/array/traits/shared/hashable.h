#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Hashable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const SharedArray<T, S>& array) noexcept {
    Hashable<Array<T, S>>::Hash(*array.Pointer());
  }

};

}
