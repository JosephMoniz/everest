#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/traits/lawful/functor.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T>
class Alternative {

  typedef Alternative<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Alt(const T& lhs, const T& rhs) noexcept {
    return Base::Alt(lhs, rhs);
  }

};

template <class T>
constexpr inline T Alt(const T& a, const T& b) noexcept {
  return Alternative<T>::Alt(a, b);
}

template <class T>
constexpr inline T operator||(const T& lhs, const T& rhs) noexcept {
  return Alternative<T>::Alt(lhs, rhs);
}

}

#pragma clang diagnostic pop
