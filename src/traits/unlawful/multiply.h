#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_MULTIPLY
#define TRAITOROUS_TRAITS_MULTIPLY 1

#include "functions/types.h"

namespace traitorous {

template <class T>
class Multipliable {

  typedef Multipliable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U Multiply(const U& lhs, const U& rhs) noexcept {
    return Base::Multiply(lhs, rhs);
  }

  template <class U>
  static constexpr inline Function<const U&, U> Multiply(const U& lhs) noexcept {
    return [&](const U& rhs) {
      return Base::Multiply(lhs, rhs);
    };
  }

};

template <class T>
class DefaultMultipliable {
public:

  static constexpr bool exists = true;

  static T Multiply(const T& lhs, const T& rhs) noexcept {
    return lhs * rhs;
  }

};

template <class T>
constexpr inline T Multiply(const T& lhs, const T& rhs) noexcept {
  return Multipliable<T>::Multiply(lhs, rhs);
}

template <class T>
constexpr inline Function<const T&, T> Multiply(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Multipliable<T>::Multiply(lhs, rhs);
  };
}

template <class T>
constexpr inline T operator*(const T& lhs, const T& rhs) noexcept {
  return Multipliable<T>::Multiply(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop
