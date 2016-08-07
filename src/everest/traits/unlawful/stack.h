#pragma once

#include <everest/containers/option.h>

namespace everest {

template <class T>
class Stack {

  typedef Stack<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T Push(const U& item, const T& stack) noexcept {
    return Base::Push(item, stack);
  }

  static T Pop(const T& stack) noexcept {
    return Base::Pop(stack);
  }

  template <class U>
  static Option<const U&> Top(const T& stack) noexcept {
    return Base::Top(stack);
  }

};

template <class T, class U>
T Push(const U& item, const T& stack) noexcept {
  static_assert(Stack<T>::exists, "T does not implement Stack");
  return Stack<T>::Push(item, stack);
};

template <class T>
T Pop(const T& stack) noexcept {
  static_assert(Stack<T>::exists, "T does not implement Stack");
  return Stack<T>::Pop(stack);
};

template <class T>
auto Top(const T& stack) noexcept -> decltype(Stack<T>::Pop(stack)) {
  static_assert(Stack<T>::exists, "T does not implement Stack");
  return Stack<T>::Top(stack);
};

}

