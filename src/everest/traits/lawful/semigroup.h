#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/functions/types.h>

namespace everest {

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
constexpr T Add(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T>
constexpr Function<const T&, T> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr BiFunction<const T&, const T&, T> Add() noexcept {
  return [&](const T& lhs, const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr T operator+(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

// These are the cases for adding two elements of differing types
//
template <class T, class U>
constexpr auto Add(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T, class U, class R>
constexpr Function<const U&, R> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
constexpr BiFunction<const T&, const U&, R> Add() noexcept {
  return [&](const T& lhs, const U& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
constexpr R operator+(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

}

#pragma clang diagnostic pop
