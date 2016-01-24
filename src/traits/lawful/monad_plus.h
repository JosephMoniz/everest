#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_MONADPLUS
#define TRAITOROUS_TRAITS_MONADPLUS 1

#include "functor.h"
#include "monad.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class monad_plus {

  typedef monad_plus<T> base;

public:

  static constexpr T mplus(const T& lhs, const T& rhs) noexcept {
    return base::mplus(lhs, rhs);
  }

  static constexpr bool exists = false;

};

template <class M>
constexpr inline M mplus(const M& a, const M& b) noexcept {
  return monad_plus<M>::mplus(a, b);
}

}

#endif

#pragma clang diagnostic pop