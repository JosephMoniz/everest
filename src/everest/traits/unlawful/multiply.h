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
  static U Multiply(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement Multipliable");
    return Base::Multiply(lhs, rhs);
  }

  template <class U>
  static Function<const U&, U> Multiply(const U& lhs) noexcept {
    static_assert(exists, "T does not implement Multipliable");
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
T Multiply(const T& lhs, const T& rhs) noexcept {
  static_assert(Multipliable<T>::exists, "T does not implement Multipliable");
  return Multipliable<T>::Multiply(lhs, rhs);
}

template <class T>
Function<const T&, T> Multiply(const T& lhs) noexcept {
  static_assert(Multipliable<T>::exists, "T does not implement Multipliable");
  return [&](const T& rhs) {
    return Multipliable<T>::Multiply(lhs, rhs);
  };
}

template <class T>
T operator*(const T& lhs, const T& rhs) noexcept {
  static_assert(Multipliable<T>::exists, "T does not implement Multipliable");
  return Multipliable<T>::Multiply(lhs, rhs);
}

}

#pragma clang diagnostic pop
