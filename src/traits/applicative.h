#ifndef TRAITOROUS_TRAITS_APPLICATIVE
#define TRAITOROUS_TRAITS_APPLICATIVE 1

#include "functor.h"

namespace traitorous {

template <class T>
struct applicative {
  // ap()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class A,
          class B,
          class = typename std::enable_if<functor<F<A>>::exists>::type,
          class = typename std::enable_if<applicative<F<A>>::exists>::type>
constexpr F<B> ap(F<std::function<B(const A&)>> f, const F<A>& a) noexcept {
  return applicative<F<A>>::ap(f, a);
}

}

#endif
