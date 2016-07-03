#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>
#include <everest/types/string.h>
#include <everest/traits/unlawful/fundamental.h>


namespace everest {

template <class T>
class Shows {

  typedef Shows<T> Base;

public:

  static constexpr bool exists = false;

  static auto Show(T&& n) noexcept {
    return Base::Show(std::forward<T>(n));
  }

};

template <class T>
String Show(const T& n) noexcept {
  return Shows<T>::Show(n);
}

template <class T>
String Show(const T* n) noexcept {
  return n == nullptr
    ? String("")
    : Shows<T>::Show(*n);
}

}

#pragma clang diagnostic pop
