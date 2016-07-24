#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_drop.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableDrop<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& DropInPlace(size_t length, MutableVector<T>& vector) noexcept {
    return vector.DropInPlace(length);
  }

  template<class Predicate>
  static MutableVector<T>& DropInPlaceWhile(Predicate predicate, MutableVector<T>& vector) noexcept {
    return vector.DropInPlaceWhile(predicate);
  }

};

}