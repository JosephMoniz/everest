#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/droppable.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Droppable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Drop(size_t length, const Vector<T>& vector) noexcept {
    return vector.Drop(length);
  }

  template<class Predicate>
  static Vector<T> DropWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    return vector.DropWhile(predicate);
  }

};

}