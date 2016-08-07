#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Subtractable {

  typedef Subtractable<T> Base;

public:

  static constexpr bool exists = false;

  static T Subtract(const T& lhs, const T& rhs) noexcept {
    return Base::Subtract(lhs, rhs);
  }

};

template <class T>
class DefaultSubtract {
public:

  static constexpr bool exists = true;

  static T Subtract(const T& lhs, const T& rhs) noexcept {
    return lhs - rhs;
  }

};

template <class T>
T Subtract(const T& lhs, const T& rhs) noexcept {
  static_assert(Subtractable<T>::exists, "T does not implement Subtractable");
  return Subtractable<T>::Subtract(lhs, rhs);
}

template <class T>
T operator-(const T& lhs, const T& rhs) noexcept {
  static_assert(Subtractable<T>::exists, "T does not implement Subtractable");
  return Subtractable<T>::Subtract(lhs, rhs);
}

}

#pragma clang diagnostic pop