#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_MONAD
#define TRAITOROUS_TRAITS_MONAD 1

#include "functor.h"

namespace traitorous {

template <template<class> class F, class T>
class Monad {

  typedef Monad<F, T> Base;

public:

  static constexpr bool exists = false;

  template <class Fn, class B = typename std::result_of<Fn(F<T>)>::type>
  static constexpr B FlatMap(Fn f, const F<T>& m) noexcept {
    return Base::FlatMap(f, m);
  }

  template <class B>
  static constexpr F<B> Then(const F<T>& m, const F<B>& n) noexcept {
    return Base::Then(m, n);
  }

};

template <template<class> class F,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type>
constexpr inline Mb FlatMap(Fn f, const F<A>& m) noexcept {
  return Monad<F, A>::FlatMap(f, m);
}

template <template<class> class F,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type>
constexpr inline Mb operator>>=(const A& m, Fn f) noexcept {
  return Monad<F, A>::FlatMap(f, m);
}

template <template <class> class F, class A, class B>
constexpr inline F<B> Then(const F<A>& a, const F<B>& b) noexcept {
  return Monad<F, A>::Then(a, b);
}

}

#endif

#pragma clang diagnostic pop