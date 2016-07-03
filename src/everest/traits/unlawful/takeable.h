#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


#include <stddef.h>
#include <everest/functions/types.h>

namespace everest {

template <class T>
class Takeable {

  typedef Takeable<T> Base;

public:

  static constexpr bool exists = false;

  /*
  static auto Take(size_t s, T&& n) noexcept -> decltype(Base::Take(s, std::forward<T>(n))) {
    return Base::Take(s, std::forward<T>(n));
  }

  template <class F, class N>
  static auto TakeWhile(Predicate<const N&> p, F&& n) noexcept -> decltype(Base::TakeWhile(p, std::forward<F>(n))) {
    return Base::TakeWhile(p, std::forward<F>(n));
  }
   */

};

template <class T>
auto Take(size_t s, const T& n) noexcept -> decltype(Takeable<T>::Take(s, n)) {
  return Takeable<T>::Take(s, n);
}

template <class T>
auto Take(size_t s, T&& n) noexcept -> decltype(Takeable<T>::Take(s, std::forward<T>(n))) {
  return Takeable<T>::Take(s, std::forward<T>(n));
}

template <class F, class T>
auto TakeWhile(Predicate<const T&> p, const F& n) noexcept -> decltype(Takeable<F>::TakeWhile(p, n)) {
  return Takeable<F>::TakeWhile(p, n);
}

template <class F, class T>
auto TakeWhile(Predicate<const T&> p, F&& n) noexcept -> decltype(Takeable<F>::TakeWhile(p, std::forward<T>(n))) {
  return Takeable<F>::TakeWhile(p, std::forward<T>(n));
}

}

#pragma clang diagnostic pop
