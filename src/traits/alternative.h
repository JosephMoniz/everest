#ifndef TRAITOROUS_TRAITS_ALTERNATIVE
#define TRAITOROUS_TRAITS_ALTERNATIVE 1

#include "applicative.h"
#include "functor.h"
#include "zero.h"

namespace traitorous {

template <class T>
struct alternative {
  // ap()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class A,
          class = typename std::enable_if<functor<F<A>>::exists>::type,
          class = typename std::enable_if<applicative<F<A>>::exists>::type,
          class = typename std::enable_if<alternative<F<A>>::exists>::type,
          class = typename std::enable_if<zero_val<F<A>>::exists>::type>
constexpr F<A>& alt(const F<A>& a, const F<A>& b) noexcept {
  return alternative<F<A>>::alt(a, b);
}

template <template <class> class F,
          class A,
          class = typename std::enable_if<functor<F<A>>::exists>::type,
          class = typename std::enable_if<applicative<F<A>>::exists>::type,
          class = typename std::enable_if<alternative<F<A>>::exists>::type,
          class = typename std::enable_if<zero_val<F<A>>::exists>::type>
constexpr F<A>& operator||(const F<A>& lhs, const F<A>& rhs) noexcept {
  return alternative<F<A>>::alt(lhs, rhs);
}

}

#endif
