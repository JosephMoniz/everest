#pragma once

#include <utility>

namespace everest {

template <class T>
class MutableQueue {

  typedef MutableQueue<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T& EnqueueInPlace(const U& item, T& stack) noexcept {
    static_assert(exists, "T does not implement MutableQueue");
    return Base::EnqueueInPlace(item, stack);
  }

  template <class U>
  static T& EnqueueInPlace(U&& item, T& stack) noexcept {
    static_assert(exists, "T does not implement MutableQueue");
    return Base::EnqueueInPlace(std::move(item), stack);
  }

  template <class U>
  static U& DequeueInPlace(T& stack) noexcept {
    static_assert(exists, "T does not implement MutableQueue");
    return Base::DequeueInPlace(stack);
  }

  template <class U>
  static U&& DequeueWithMove(T& stack) noexcept {
    static_assert(exists, "T does not implement MutableQueue");
    return Base::DequeueWithMove(stack);
  }

};

template <class T, class U>
T& EnqueueInPlace(const U& item, T& stack) noexcept {
  static_assert(MutableQueue<T>::exists, "T does not implement MutableQueue");
  return MutableQueue<T>::EnqueueInPlace(item, stack);
};

template <class T, class U>
T& EnqueueInPlace(U&& item, T& stack) noexcept {
  static_assert(MutableQueue<T>::exists, "T does not implement MutableQueue");
  return MutableQueue<T>::EnqueueInPlace(std::move(item), stack);
};

template <class T, class U>
U& DequeueInPlace(T& stack) noexcept {
  static_assert(MutableQueue<T>::exists, "T does not implement MutableQueue");
  return MutableQueue<T>::DequeueInPlace(stack);
};

template <class T, class U>
U& DequeueWithMove(T& stack) noexcept {
  static_assert(MutableQueue<T>::exists, "T does not implement MutableQueue");
  return MutableQueue<T>::DequeueWithMove(stack);
};

}

