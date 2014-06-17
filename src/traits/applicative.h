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
constexpr F<B> ap(const F<Fn>& f, const F<A>& a) noexcept {
  return applicative<F<Fn>>::ap(f, a);
}

}

#endif
