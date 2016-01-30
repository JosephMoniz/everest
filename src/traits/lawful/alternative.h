#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_ALTERNATIVE
#define TRAITOROUS_TRAITS_ALTERNATIVE 1

#include "functor.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class Alternative {

  typedef Alternative<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Alt(const T& lhs, const T& rhs) noexcept {
    return Base::Alt(lhs, rhs);
  }

};

template <class T>
constexpr inline T Alt(const T& a, const T& b) noexcept {
  return Alternative<T>::Alt(a, b);
}

template <class T>
constexpr inline T operator||(const T& lhs, const T& rhs) noexcept {
  return Alternative<T>::Alt(lhs, rhs);
}

}

#endif
#pragma clang diagnostic pop
