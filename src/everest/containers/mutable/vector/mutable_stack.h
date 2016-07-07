#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_stack.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableStack<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& PushInPlace(const T& item, MutableVector<T>& vector) noexcept {
    if (vector._memory == nullptr || vector._length == Length(vector._memory)) {
      vector.Reserve((size_t) (Length(vector._memory) * 1.5));
    }
    MutablePointer(vector._memory)[vector._length++] = item;
    return vector;
  }

  static MutableVector<T>& PushInPlace(T&& item, MutableVector<T>& vector) noexcept {
    if (vector._memory == nullptr || vector._length == Length(vector._memory)) {
      vector.Reserve((size_t) (Length(vector._memory) * 1.5));
    }
    MutablePointer(vector._memory)[vector._length++] = std::move(item);
    return vector;
  }

  static MutableVector<T>& PopInPlace(MutableVector<T>& vector) noexcept {
    if (vector._length > 0) {
      vector._length--;
    }
    return vector;
  }

};

}
