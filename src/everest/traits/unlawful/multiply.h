#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/functions/types.h>

namespace everest {

template <class T>
class Multipliable {

  typedef Multipliable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr U Multiply(const U& lhs, const U& rhs) noexcept {
    return Base::Multiply(lhs, rhs);
  }

  template <class U>
  static constexpr Function<const U&, U> Multiply(const U& lhs) noexcept {
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
constexpr T Multiply(const T& lhs, const T& rhs) noexcept {
  return Multipliable<T>::Multiply(lhs, rhs);
}

template <class T>
constexpr Function<const T&, T> Multiply(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Multipliable<T>::Multiply(lhs, rhs);
  };
}

template <class T>
constexpr T operator*(const T& lhs, const T& rhs) noexcept {
  return Multipliable<T>::Multiply(lhs, rhs);
}

}

#pragma clang diagnostic pop
