#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/droppable.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T>
class Droppable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Drop(size_t length, const Vector<T>& vector) noexcept {
    auto vectorLength = vector.Length();
    auto offset       = Min(length, length);
    return Vector<T>(Memory<T>(vector.Pointer()[offset], vectorLength - offset));
  }

  template<class Predicate>
  static Vector<T> DropWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = vector.Length();
    auto pointer  = vector.Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return Vector<T>(Memory<T>(pointer[offset], length - offset));
  }

};

}