#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_ALTERNATIVE
#define TRAITOROUS_TRAITS_ALTERNATIVE 1

#include "functor.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class alternative {

  typedef alternative<T> base;

public:

  static constexpr T alt(const T& lhs, const T& rhs) noexcept {
    return base::alt(lhs, rhs);
  }

  static constexpr bool exists = false;
};

template <class T>
constexpr inline T alt(const T& a, const T& b) noexcept {
  return alternative<T>::alt(a, b);
}

template <class T>
constexpr inline T operator||(const T& lhs, const T& rhs) noexcept {
  return alternative<T>::alt(lhs, rhs);
}

}

#endif
#pragma clang diagnostic pop
