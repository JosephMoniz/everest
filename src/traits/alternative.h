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

template <class F,
          class = typename std::enable_if<functor<F>::exists>::type,
          class = typename std::enable_if<applicative<F>::exists>::type,
          class = typename std::enable_if<alternative<F>::exists>::type,
          class = typename std::enable_if<zero_val<F>::exists>::type>
constexpr inline F alt(const F& a, const F& b) noexcept {
  return alternative<F>::alt(a, b);
}

template <class F,
          class = typename std::enable_if<functor<F>::exists>::type,
          class = typename std::enable_if<applicative<F>::exists>::type,
          class = typename std::enable_if<alternative<F>::exists>::type,
          class = typename std::enable_if<zero_val<F>::exists>::type>
constexpr inline F operator||(const F& lhs, const F& rhs) noexcept {
  return alternative<F>::alt(lhs, rhs);
}

}

#endif
