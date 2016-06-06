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

  static constexpr T Take(size_t s, const T& n) noexcept {
    return Base::Take(s, n);
  }

  template <class F, class N>
  static constexpr F TakeWhile(Predicate<const N&> p, const F& n) noexcept {
    return Base::TakeWhile(p, n);
  }

};

template <class T>
constexpr T Take(size_t s, const T& n) noexcept {
  return Takeable<T>::Take(s, n);
}

template <class F, class T>
constexpr F TakeWhile(Predicate<const T&> p, const F& n) noexcept {
  return Takeable<F>::TakeWhile(p, n);
}

}

#pragma clang diagnostic pop
