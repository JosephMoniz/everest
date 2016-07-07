#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Hashable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static int Hash(const Vector<T>& vector) noexcept {
    return Hashable<MutableVector<T>>::Hash(vector._wrapped);
  }

};

}