#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Containable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const Vector<T>& vector) noexcept {
    return Containable<MutableVector<T>>::Contains(n, vector._wrapped);
  }

};

}