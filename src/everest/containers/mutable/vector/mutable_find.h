#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableFind<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static T* FindInPlace(Predicate predicate, MutableVector<T>& vector) noexcept {
    return vector.FindInPlace(predicate);
  }

};

}