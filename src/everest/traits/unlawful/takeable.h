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

  static T Take(size_t s, T&& n) noexcept {
    static_assert(exists, "T does not implement Takeable");
    return Base::Take(s, std::forward<T>(n));
  }

  template <class F, class N>
  static T TakeWhile(Predicate<const N&> p, F&& n) noexcept {
    static_assert(exists, "T does not implement Takeable");
    return Base::TakeWhile(p, std::forward<F>(n));
  }

};

template <class T>
T Take(size_t s, const T& n) noexcept {
  static_assert(Takeable<T>::exists, "T does not implement Takeable");
  return Takeable<T>::Take(s, n);
}

template <class T>
T Take(size_t s, T&& n) noexcept {
  static_assert(Takeable<T>::exists, "T does not implement Takeable");
  return Takeable<T>::Take(s, std::forward<T>(n));
}

template <class F, class T>
F TakeWhile(Predicate<const T&> p, const F& n) noexcept {
  static_assert(Takeable<T>::exists, "T does not implement Takeable");
  return Takeable<F>::TakeWhile(p, n);
}

template <class F, class T>
F TakeWhile(Predicate<const T&> p, F&& n) noexcept {
  static_assert(Takeable<T>::exists, "T does not implement Takeable");
  return Takeable<F>::TakeWhile(p, std::forward<T>(n));
}

}

#pragma clang diagnostic pop
