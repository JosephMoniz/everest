#pragma once

#include <everest/containers/option.h>

namespace everest {

template <class T>
class Queue {

  typedef Queue<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T Enqueue(const U& item, const T& queue) noexcept {
    return Base::Enqueue(item, queue);
  }

  static T Dequeue(const T& queue) noexcept {
    return Base::Dequeue(queue);
  }

  template <class U>
  static Option<U> Front(const T& queue) noexcept {
    return Base::Front(queue);
  }

};

template <class T, class U>
T Enqueue(const U& item, const T& queue) noexcept {
  static_assert(Queue<T>::exists, "T does not implement Queue");
  return Queue<T>::Enqueue(item, queue);
};

template <class T>
T Dequeue(const T& queue) noexcept {
  static_assert(Queue<T>::exists, "T does not implement Queue");
  return Queue<T>::Dequeue(queue);
};

template <class T>
auto Front(const T& queue) noexcept -> decltype(Queue<T>::Front(queue)) {
  static_assert(Queue<T>::exists, "T does not implement Queue");
  return Queue<T>::Front(queue);
};

}
