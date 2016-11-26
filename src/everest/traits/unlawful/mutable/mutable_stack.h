#pragma once

#include <utility>

namespace everest {

template <class T>
class MutableStack {

  typedef MutableStack<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T& PushInPlace(const U& item, T& stack) noexcept {
    static_assert(exists, "T does not implement MutableStack");
    return Base::PushInPlace(item, stack);
  }

  template <class U>
  static T& PushInPlace(U&& item, T& stack) noexcept {
    static_assert(exists, "T does not implement MutableStack");
    return Base::PushInPlace(std::move(item), stack);
  }

  static T& PopInPlace(T& stack) noexcept {
    static_assert(exists, "T does not implement MutableStack");
    return Base::PopInPlace(stack);
  }

};

template <class T, class U>
T& PushInPlace(const U& item, T& stack) noexcept {
  static_assert(MutableStack<T>::exists, "T does not implement MutableStack");
  return MutableStack<T>::PushInPlace(item, stack);
};

template <class T, class U>
T& PushInPlace(U&& item, T& stack) noexcept {
  static_assert(MutableStack<T>::exists, "T does not implement MutableStack");
  return MutableStack<T>::PushInPlace(std::move(item), stack);
};

template <class T>
T& PopInPlace(T& stack) noexcept {
  static_assert(MutableStack<T>::exists, "T does not implement MutableStack");
  return MutableStack<T>::PopInPlace(stack);
};

}

