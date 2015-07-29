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

template <class M,
          class = typename std::enable_if<functor<M>::exists>::type,
          class = typename std::enable_if<applicative<M>::exists>::type,
          class = typename std::enable_if<monad<M>::exists>::type,
          class = typename std::enable_if<zero_val<M>::exists>::type>
constexpr inline M mplus(const M& a, const M& b) noexcept {
  return monad_plus<M>::mplus(a, b);
}

}

#endif
