#ifndef TRAITOROUS_TRAITS_UNLAWFUL_QUEUE_H
#define TRAITOROUS_TRAITS_UNLAWFUL_QUEUE_H

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
    return Base::Dequeue(item, queue);
  }

  template <class U>
  static LocalOption<U> Front(const T& queue) noexcept {
    return Base::Front(queue);
  }

};

template <class T, class U>
constexpr T Enqueue(const U& item, const T& queue) noexcept {
  return Queue<T>::Enqueue(item, stack);
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

#endif
