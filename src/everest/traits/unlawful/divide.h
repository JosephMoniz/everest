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
  static U Divide(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement Dividable");
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
T Divide(const T& lhs, const T& rhs) noexcept {
  static_assert(Dividable<T>::exists, "T does not implement Dividable");
  return Dividable<T>::Divide(lhs, rhs);
}

template <class T>
T operator/(const T& lhs, const T& rhs) noexcept {
  static_assert(Dividable<T>::exists, "T does not implement Dividable");
  return Dividable<T>::Divide(lhs, rhs);
}

}

#pragma clang diagnostic pop