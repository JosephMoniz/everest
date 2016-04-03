#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Containable<SharedArray<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const SharedArray<T, S>& array) noexcept {
    return Containable<MutableArray<T, S>, T>::Contains(n, *array.Pointer());
  }

};

}
