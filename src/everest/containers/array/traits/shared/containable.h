#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Containable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const SharedArray<T, S>& array) noexcept {
    return Containable<Array<T, S>>::Contains(n, *array);
  }

};

}
