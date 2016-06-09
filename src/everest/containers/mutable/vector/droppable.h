#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/droppable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Droppable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Drop(size_t length, const MutableVector<T>& vector) noexcept {
    auto vectorLength = Length(vector);
    auto offset       = Min(length, vectorLength);
    auto pointer      = Pointer(vector);
    return MutableVector<T>(MutableMemory<T>(pointer[offset], vectorLength - offset));
  }

  template<class Predicate>
  static MutableVector<T> DropWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer[offset], length - offset));
  }

};

}