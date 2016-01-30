#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_UNWRAPPABLE
#define TRAITOROUS_TRAITS_UNWRAPPABLE 1

#include <functional>

namespace traitorous {

template <class T>
class Unwrappable {

  typedef Unwrappable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class D, class U = typename std::result_of<D()>::type>
  static constexpr inline U GetOrElse(D d, const F& f) noexcept {
    return Base::GetOrElse(d, f);
  }


  template <class F, class U>
  static constexpr inline U GetOrDefault(const U& f, const F& n) noexcept {
    return Base::GetOrDefault(f, n);
  }

};

template <class F, class D, class T = typename std::result_of<D()>::type>
constexpr inline T GetOrElse(D d, const F& f) noexcept {
  return Unwrappable<F>::GetOrElse(d, f);
}


template <class F, class T>
constexpr inline T GetOrDefault(const T& f, const F& n) noexcept {
  return Unwrappable<F>::GetOrDefault(f, n);
}

}

#endif

#pragma clang diagnostic pop