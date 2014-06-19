#ifndef TRAITOROUS_TRAITS_MONADPLUS
#define TRAITOROUS_TRAITS_MONADPLUS 1

#include "applicative.h"
#include "functor.h"
#include "monad.h"
#include "zero.h"

namespace traitorous {

template <class T>
struct monad_plus {
  // mplus()
  static constexpr bool exists = false;
};

template <template <class> class M,
          class A,
          class = typename std::enable_if<functor<M<A>>::exists>::type,
          class = typename std::enable_if<applicative<M<A>>::exists>::type,
          class = typename std::enable_if<monad<M<A>>::exists>::type,
          class = typename std::enable_if<zero_val<M<A>>::exists>::type>
constexpr inline M<A> mplus(const M<A>& a, const M<A>& b) noexcept {
  return monad_plus<M<A>>::mplus(a, b);
}

}

#endif
