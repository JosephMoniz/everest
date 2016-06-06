#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Containable<SharedMutableArray<T, S>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const SharedMutableArray<T, S>& array) noexcept {
    return Containable<MutableArray<T, S>, T>::Contains(n, *array);
  }

};

}
