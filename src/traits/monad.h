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
          class A,
          class B,
          class = typename std::enable_if<functor<M<A>>::exists>::type,
          class = typename std::enable_if<applicative<M<A>>::exists>::type>
constexpr M<B> flatMap(const M<A>& m,
                       std::function<M<B>(const A&)> f) noexcept
{
  return monad<M<A>>::flatMap(m, f);
}

template <template <class> class M,
          class A,
          class B,
          class = typename std::enable_if<functor<M<A>>::exists>::type,
          class = typename std::enable_if<applicative<M<A>>::exists>::type>
constexpr M<B> then(const M<A>& a, const M<A>& b) noexcept {
  return monad<M<A>>::then(a, b);
}

}

#endif
