#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/Pointable.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Pointable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const SharedArray<T, S>& array) noexcept {
    return Pointable<Array<T, S>>::Pointer(*array);
  }

};

}