#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_TAKEABLE
#define TRAITOROUS_TRAITS_TAKEABLE 1

#include <functional>

namespace traitorous {

template <class T>
class Takeable {

  typedef Takeable<T> Base;

public:

  static constexpr bool exists = false;

  template <class T>
  static constexpr inline T Take(const T& n, unsigned int s) noexcept {
    return Base::Take(n, s);
  }

  template <template <class> class F, class T>
  static constexpr inline F<T> TakeWhile(const F<T>& n, std::function<bool(const T&)> p) noexcept {
    return Base::TakeWhile(n, p);
  }

};

template <class T>
constexpr inline T Take(const T& n, unsigned int s) noexcept {
  return Takeable<T>::Take(n, s);
}

template <template <class> class F,
  class T>
constexpr inline F<T> TakeWhile(const F<T>& n, std::function<bool(const T&)> p) noexcept {
  return Takeable<F<T>>::TakeWhile(n, p);
}

}

#endif

#pragma clang diagnostic pop