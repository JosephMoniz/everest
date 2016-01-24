#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_MONAD
#define TRAITOROUS_TRAITS_MONAD 1

#include "functor.h"

namespace traitorous {

template <template<class> class F, class T>
class monad {

  typedef monad<F, T> base;

public:

  template <class Fn, class B = typename std::result_of<Fn(F<T>)>::type>
  static constexpr B flat_map(Fn f, const F<T>& m) noexcept {
    return base::flat_map(f, m);
  }

  template <class B>
  static constexpr F<B> then(const F<T>& m, const F<B>& n) noexcept {
    return base::then(m, n);
  }

  static constexpr bool exists = false;

};

template <template<class> class F,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type>
constexpr inline Mb flat_map(Fn f, const F<A>& m) noexcept {
  return monad<F, A>::flat_map(f, m);
}

template <template<class> class F,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type>
constexpr inline Mb operator>>=(const A& m, Fn f) noexcept {
  return monad<F, A>::flat_map(f, m);
}

template <template <class> class F, class A, class B>
constexpr inline F<B> then(const F<A>& a, const F<B>& b) noexcept {
  return monad<F, A>::then(a, b);
}

}

#endif

#pragma clang diagnostic pop