#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Queue<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Enqueue(const T& item, const MutableVector<T>& vector) noexcept {
    return vector.Enqueue(item);
  }

  static MutableVector<T> Dequeue(const MutableVector<T>& vector) noexcept {
    return vector.Dequeue();
  }

  static Option<const T&> Front(const MutableVector<T>& vector) noexcept {
    return vector.Front();
  }

};

}