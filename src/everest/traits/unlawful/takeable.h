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

  static constexpr inline T Take(const T& n, size_t s) noexcept {
    return Base::Take(n, s);
  }

  template <class F, class N>
  static constexpr inline F TakeWhile(const F& n, Predicate<const N&> p) noexcept {
    return Base::TakeWhile(n, p);
  }

};

template <class T>
constexpr inline T Take(const T& n, size_t s) noexcept {
  return Takeable<T>::Take(n, s);
}

template <class F, class T>
constexpr inline F TakeWhile(const F& n, Predicate<const T&> p) noexcept {
  return Takeable<F>::TakeWhile(n, p);
}

}

#pragma clang diagnostic pop
