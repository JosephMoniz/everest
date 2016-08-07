#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/droppable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Droppable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Drop(size_t length, const MutableVector<T>& vector) noexcept {
    return vector.Drop(length);
  }

  template<class Predicate>
  static MutableVector<T> DropWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    return vector.DropWhile(predicate);
  }

};

}