#ifndef TRAITOROUS_TRAITS_APPLICATIVE
#define TRAITOROUS_TRAITS_APPLICATIVE 1

#include <functional>
#include <type_traits>

#include "functor.h"

namespace traitorous {

template <class T>
struct applicative {
  // ap()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class Fn,
          class A,
          class B = typename std::result_of<Fn(A)>::type,
          class   = typename std::enable_if<functor<F<A>>::exists>::type,
          class   = typename std::enable_if<applicative<F<A>>::exists>::type>
constexpr inline F<B> ap(const F<Fn>& f, const F<A>& a) noexcept {
  return applicative<F<Fn>>::ap(f, a);
}

template <template <class, class> class F,
          class Fn,
          class A,
          class B,
          class R = typename std::result_of<Fn(B)>::type,
          class   = typename std::enable_if<functor<F<A, B>>::exists>::type,
          class   = typename std::enable_if<applicative<F<A, B>>::exists>::type>
constexpr inline F<A, R> ap(const F<A, Fn>& f, const F<A, B>& a) noexcept {
  return applicative<F<A, B>>::ap(f, a);
}

}

#endif
