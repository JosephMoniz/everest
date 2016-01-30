#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_SUBTRACT
#define TRAITOROUS_TRAITS_SUBTRACT 1

namespace traitorous {

template <class T>
class Subtractable {

  typedef Subtractable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U Subtract(const U& lhs, const U& rhs) noexcept {
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
constexpr inline T Subtract(const T& lhs, const T& rhs) noexcept {
  return Subtractable<T>::Subtract(lhs, rhs);
}

template <class T>
constexpr inline T operator-(const T& lhs, const T& rhs) noexcept {
  return Subtractable<T>::Subtract(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop