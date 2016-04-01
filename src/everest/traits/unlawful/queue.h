#pragma once

#include <everest/containers/option.h>

namespace traitorous {

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
constexpr T Enqueue(const U& item, const T& queue) noexcept {
  return Queue<T>::Enqueue(item, queue);
};

template <class T>
constexpr T Dequeue(const T& queue) noexcept {
  return Queue<T>::Dequeue(queue);
};

template <class T>
constexpr auto Front(const T& queue) noexcept -> decltype(Queue<T>::Front(queue)) {
  return Queue<T>::Front(queue);
};

}
