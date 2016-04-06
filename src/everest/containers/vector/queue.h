#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template <class T>
class Queue<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Enqueue(const T& item, const Vector<T>& vector) noexcept {
    auto capacity = vector.Length() + 1;
    auto memory   = MutableMemory<T>(vector.Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return Vector<T>(Memory<T>(memory));
  }

  static Vector<T> Dequeue(const Vector<T>& vector) noexcept {
    if (vector.Length() > 0) {
      return Vector<T>(Memory<T>(vector.Pointer()[1], vector.Length() - 1));
    } else {
      return Vector<T>();
    }
  }

  static Option<const T&> Front(const Vector<T>& vector) noexcept {
    return vector.At(0);
  }

};

}