#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <limits>

namespace everest {

template <class T>
class Bounded {

  typedef Bounded<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static U MinValue() noexcept {
    static_assert(exists, "T does not implement Bounded");
    return Base::MinValue();
  }

  template <class U>
  static U MaxValue() noexcept {
    static_assert(exists, "T does not implement Bounded");
    return Base::MaxValue();
  }

};

template <class T>
class DefaultBounded {
public:

  static constexpr bool exists = true;

  static T MinValue() noexcept {
    return std::numeric_limits<T>::min();
  }

  static T MaxValue() noexcept {
    return std::numeric_limits<T>::max();
  }

};

template <class T>
T MinValue() noexcept {
  static_assert(Bounded<T>::exists, "T does not implement Bounded");
  return Bounded<T>::MinValue();
}

template <class T>
T MaxValue() noexcept {
  static_assert(Bounded<T>::exists, "T does not implement Bounded");
  return Bounded<T>::MaxValue();
}

}

#pragma clang diagnostic pop