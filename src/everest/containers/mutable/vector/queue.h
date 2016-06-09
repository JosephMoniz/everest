#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Queue<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Enqueue(const T& item, const MutableVector<T>& vector) noexcept {
    auto capacity = Length(vector) + 1;
    auto memory   = MutableMemory<T>(Pointer(vector), capacity);
    MutablePointer(memory)[capacity] = item;
    return MutableVector<T>(memory);
  }

  static MutableVector<T> Dequeue(const MutableVector<T>& vector) noexcept {
    if (Length(vector) > 0) {
      return MutableVector<T>(MutableMemory<T>(Pointer(vector)[1], Length(vector) - 1));
    } else {
      return MutableVector<T>();
    }
  }

  static Option<const T&> Front(const MutableVector<T>& vector) noexcept {
    return vector.At(0);
  }

};

}