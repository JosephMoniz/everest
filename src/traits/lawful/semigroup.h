#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_SEMIGROUP
#define TRAITOROUS_TRAITS_SEMIGROUP 1

#include <functional>

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

template <class T>
constexpr inline T Add(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

template <class T>
constexpr inline std::function<T(const T&)> Add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr inline std::function<T(const T&, const T&)> Add() noexcept {
  return [&](const T& lhs, const T& rhs) {
    return Semigroup<T>::Add(lhs, rhs);
  };
}

template <class T>
constexpr inline T operator+(const T& lhs, const T& rhs) noexcept {
  return Semigroup<T>::Add(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop