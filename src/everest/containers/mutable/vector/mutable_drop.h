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
    auto vectorLength = Length(vector);
    auto offset       = Min(length, vectorLength);
    auto pointer      = MutablePointer(vector);
    for (auto i = 0; i + offset < vectorLength; i++) {
      pointer[i] = pointer[i + offset];
    }
    vector._length -= offset;
    return vector;
  }

  template<class Predicate>
  static MutableVector<T>& DropInPlaceWhile(Predicate predicate, MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    for (auto i = 0; i + offset < length; i++) {
      pointer[i] = pointer[i + offset];
    }
    vector._length -= offset;
    return vector;
  }

};

}