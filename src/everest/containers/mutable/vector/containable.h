#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Containable<MutableVector<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const MutableVector<T>& vector) noexcept {
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (pointer[i] == n) {
        return true;
      }
    }
    return false;
  }

};

}