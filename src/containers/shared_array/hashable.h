#pragma once

#include "containers/array.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

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
