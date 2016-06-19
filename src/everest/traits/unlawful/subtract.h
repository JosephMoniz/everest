#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Subtractable {

  typedef Subtractable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Subtract(const T& lhs, const T& rhs) noexcept {
    return Base::Subtract(lhs, rhs);
  }

};

template <class T>
class DefaultSubtract {
public:

  static constexpr bool exists = true;

  static constexpr T Subtract(const T& lhs, const T& rhs) noexcept {
    return lhs - rhs;
  }

};

template <class T>
constexpr T Subtract(const T& lhs, const T& rhs) noexcept {
  return Subtractable<T>::Subtract(lhs, rhs);
}

template <class T>
constexpr T operator-(const T& lhs, const T& rhs) noexcept {
  return Subtractable<T>::Subtract(lhs, rhs);
}

}

#pragma clang diagnostic pop