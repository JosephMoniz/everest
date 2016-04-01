#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/containers/shared.h>

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
