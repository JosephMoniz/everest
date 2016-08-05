#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/findable.h>

namespace everest {

template <class T>
class MutableVector;

template <class T>
class Findable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Find(const T& item, MutableVector<T>& vector) noexcept {
    return vector.Find(item);
  }

};

}