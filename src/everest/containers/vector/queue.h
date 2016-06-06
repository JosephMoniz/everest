#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Queue<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Enqueue(const T& item, const Vector<T>& vector) noexcept {
    return Vector<T>(Queue<MutableVector<T>>::Enqueue(item, vector._wrapped));
  }

  static Vector<T> Dequeue(const Vector<T>& vector) noexcept {
    return Vector<T>(Queue<MutableVector<T>>::Dequeue(vector._wrapped));
  }

  static Option<const T&> Front(const Vector<T>& vector) noexcept {
    return Queue<MutableVector<T>>::Front(vector._wrapped);
  }

};

}