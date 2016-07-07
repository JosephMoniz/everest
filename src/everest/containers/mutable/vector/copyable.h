#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Copyable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Copy(const MutableVector<T>& vector) noexcept {
    auto copy = MutableVector<T>();
    ForEach(vector, [&](const T& item) {
      PushInPlace(Copyable<T>::Copy(item), copy);
    });
    return copy;
  }

};

}