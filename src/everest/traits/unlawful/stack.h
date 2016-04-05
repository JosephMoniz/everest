#pragma once

#include <everest/containers/option.h>

namespace everest {

template <class T>
struct Stack {

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
constexpr T Push(const U& item, const T& stack) noexcept {
  return Stack<T>::Push(item, stack);
};

template <class T>
constexpr T Pop(const T& stack) noexcept {
  return Stack<T>::Pop(stack);
};

template <class T>
constexpr auto Top(const T& stack) noexcept -> decltype(Stack<T>::Pop(stack)) {
  return Stack<T>::Top(stack);
};

}

