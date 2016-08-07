#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableFind<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static T* FindInPlace(const T& item, MutableVector<T>& vector) noexcept {
    return vector.FindInPlace(item);
  }

};

}