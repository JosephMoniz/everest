#ifndef TRAITOROUS_TRAITS_MONAD
#define TRAITOROUS_TRAITS_MONAD 1

#include "functor.h"
#include "applicative.h"

namespace traitorous {

template <class T>
struct monad {
  // flatMap()
  // then()
  static constexpr bool exists = false;
};

template <template <class> class M,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type,
          class    = typename std::enable_if<functor<M<A>>::exists>::type,
          class    = typename std::enable_if<applicative<M<A>>::exists>::type>
constexpr inline Mb flat_map(Fn f, const M<A>& m) noexcept {
  return monad<M<A>>::flat_map(f, m);
}

template <template <class> class M,
          class Fn,
          class A,
          class Mb = typename std::result_of<Fn(A)>::type,
          class    = typename std::enable_if<functor<M<A>>::exists>::type,
          class    = typename std::enable_if<applicative<M<A>>::exists>::type>
constexpr inline Mb operator>>=(const M<A>& m, Fn f) noexcept {
  return monad<M<A>>::flat_map(f, m);
}

template <template <class> class M,
          class A,
          class B,
          class = typename std::enable_if<functor<M<A>>::exists>::type,
          class = typename std::enable_if<applicative<M<A>>::exists>::type>
constexpr inline M<B> then(const M<A>& a, const M<B>& b) noexcept {
  return monad<M<A>>::then(a, b);
}

}

#endif
