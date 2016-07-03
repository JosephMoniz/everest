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

  static T Add(const T& lhs, const T& rhs) {
    return Base::Add(lhs, rhs);
  }

};

template <class T>
class DefaultSemigroup {
public:

  static constexpr bool exists = true;

  static T Add(const T& lhs, const T& rhs) noexcept {
    return lhs + rhs;
  }

};


// These are the cases for adding two elements of the same type
//
template <class T>
T Add(T&& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(std::move(lhs), rhs);
}

template <class T>
T Add(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T>
Function<const T&, T> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
BiFunction<const T&, const T&, T> Add() noexcept {
  return [&](const T& lhs, const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
T operator+(T&& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(std::move(lhs), rhs);
}

template <class T>
T operator+(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

// These are the cases for adding two elements of differing types
//
template <class T, class U>
auto Add(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T, class U, class R>
Function<const U&, R> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
BiFunction<const T&, const U&, R> Add() noexcept {
  return [&](const T& lhs, const U& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T, class U, class R>
R operator+(const T& lhs, const U& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

}

#pragma clang diagnostic pop
