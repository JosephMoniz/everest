#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Dividable {

  typedef Dividable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U Divide(const U& lhs, const U& rhs) noexcept {
    return Base::Divide(lhs, rhs);
  }

};

template <class T>
class DefaultDividable {
public:

  static constexpr bool exists = true;

  static T Divide(const T& lhs, const T& rhs) noexcept {
    return lhs / rhs;
  }

};

template <class T>
constexpr inline T Divide(const T& lhs, const T& rhs) noexcept {
  return Dividable<T>::Divide(lhs, rhs);
}

template <class T>
constexpr inline T operator/(const T& lhs, const T& rhs) noexcept {
  return Dividable<T>::Divide(lhs, rhs);
}

}

#pragma clang diagnostic pop