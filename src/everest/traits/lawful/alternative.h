#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/traits/lawful/functor.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T>
class Alternative final {

  typedef Alternative<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Alt(const T& lhs, const T& rhs) noexcept {
    return Base::Alt(lhs, rhs);
  }

};

template <class T>
auto Alt(T&& a, T&& b) noexcept -> decltype(Alternative<T>::Alt(std::forward<T>(a), std::forward<T>(b))) {
  return Alternative<T>::Alt(std::forward<T>(a), std::forward<T>(b));
}

template <class T>
auto operator||(T&& lhs, T&& rhs) noexcept -> decltype(Alternative<T>::Alt(std::forward<T>(lhs), std::forward<T>(rhs))) {
  return Alternative<T>::Alt(std::forward<T>(lhs), std::forward<T>(rhs));
}

}

#pragma clang diagnostic pop
