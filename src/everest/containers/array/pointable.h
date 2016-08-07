#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Pointable<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Array<T, S>& array) noexcept {
    return array.Pointer();
  }

};

}
