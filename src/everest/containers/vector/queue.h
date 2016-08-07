#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Queue<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Enqueue(const T& item, const Vector<T>& vector) noexcept {
    return vector.Enqueue(item);
  }

  static Vector<T> Dequeue(const Vector<T>& vector) noexcept {
    return vector.Dequeue();
  }

  static Option<const T&> Front(const Vector<T>& vector) noexcept {
    return vector.Front();
  }

};

}