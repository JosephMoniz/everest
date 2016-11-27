#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>
#include <everest/strings/string.h>

namespace everest {

template <class T>
class Shows {

  typedef Shows<T> Base;

public:

  static constexpr bool exists = false;

  static auto Show(T& n) noexcept {
    return Base::Show(std::forward<T>(n));
  }

};

template <class T, class U = typename std::remove_const<typename std::remove_reference<T>::type>::type>
String Show(T&& object) noexcept {
  static_assert(Shows<U>::exists, "T does not implement Shows");
  return Shows<U>::Show(std::forward<T>(object));
}

template <class T>
String Show(const T* pointer) noexcept {
  static_assert(Shows<T>::exists, "T does not implement Shows");
  return pointer == nullptr
    ? String("")
    : Shows<T>::Show(*pointer);
}

}

#pragma clang diagnostic pop
