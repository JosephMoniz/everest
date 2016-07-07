#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Pointable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Vector<T>& vector) noexcept {
    return Pointable<MutableVector<T>>::Pointer(vector._wrapped);
  }

};

}
