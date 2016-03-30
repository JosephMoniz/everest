#pragma once

#include "containers/array.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Containable<SharedArray<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const SharedArray<T, S>& array) noexcept {
    return Containable<Array<T, S>, T>::Contains(n, *array.Pointer());
  }

};

}
