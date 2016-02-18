#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_SEMIGROUP
#define TRAITOROUS_TRAITS_SEMIGROUP 1

#include <functional>

#include "functions/types.h"

namespace traitorous {

template <class T>
class Semigroup {

  typedef Semigroup<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Add(const T& lhs, const T& rhs) {
    return Base::Add(lhs, rhs);
  }

};

template <class T>
class DefaultSemigroup {
public:

  static constexpr bool exists = true;

  static constexpr T Add(const T& lhs, const T& rhs) noexcept {
    return lhs + rhs;
  }

};


// These are the cases for adding two elements of the same type
//
template <class T>
constexpr inline T Add(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T>
constexpr inline Function<const T&, T> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr inline BiFunction<const T&, const T&, T> Add() noexcept {
  return [&](const T& lhs, const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr inline T operator+(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

// These are the cases for adding two elements of differing types
//
template <class T, class U>
constexpr inline auto Add(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T, class U, class R>
constexpr inline Function<const U&, R> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
constexpr inline BiFunction<const T&, const U&, R> Add() noexcept {
  return [&](const T& lhs, const U& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
constexpr inline R operator+(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop
