#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <limits>

namespace traitorous {

template <class T>
class Bounded {

  typedef Bounded<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U MinValue() noexcept {
    return Base::MinValue();
  }

  template <class U>
  static constexpr inline U MaxValue() noexcept {
    return Base::MaxValue();
  }

};

template <class T>
class DefaultBounded {
public:

  static constexpr bool exists = true;

  static constexpr T MinValue() noexcept {
    return std::numeric_limits<T>::min();
  }

  static constexpr T MaxValue() noexcept {
    return std::numeric_limits<T>::max();
  }

};

template <class T>
constexpr inline T MinValue() noexcept {
  return Bounded<T>::MinValue();
}

template <class T>
constexpr inline T MaxValue() noexcept {
  return Bounded<T>::MaxValue();
}

}

#pragma clang diagnostic pop