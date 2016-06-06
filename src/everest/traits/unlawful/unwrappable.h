#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <functional>

namespace everest {

template <class T>
class Unwrappable {

  typedef Unwrappable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class D, class U = typename std::result_of<D()>::type>
  static constexpr U GetOrElse(D d, const F& f) noexcept {
    return Base::GetOrElse(d, f);
  }


  template <class F, class U>
  static constexpr U GetOrDefault(const U& f, const F& n) noexcept {
    return Base::GetOrDefault(f, n);
  }

};

template <class F, class D, class T = typename std::result_of<D()>::type>
constexpr T GetOrElse(D d, const F& f) noexcept {
  return Unwrappable<F>::GetOrElse(d, f);
}


template <class F, class T>
constexpr T GetOrDefault(const T& f, const F& n) noexcept {
  return Unwrappable<F>::GetOrDefault(f, n);
}

}

#pragma clang diagnostic pop