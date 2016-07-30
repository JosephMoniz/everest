#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Container<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Vector<T>& vector) noexcept {
    return Container<MutableVector<T>>::Length(vector._wrapped);
  }

  static bool IsEmpty(const Vector<T>& vector) noexcept {
    return Container<MutableVector<T>>::IsEmpty(vector._wrapped);
  }

};

}