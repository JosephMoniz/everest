#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Container<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableVector<T>& vector) noexcept {
    return vector._length;
  }

  static constexpr bool IsEmpty(const MutableVector<T>& vector) noexcept {
    return vector._length == 0;
  }

};

}