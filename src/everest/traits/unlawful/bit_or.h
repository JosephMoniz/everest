#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace traitorous {

template <class T>
class BitOr {

  typedef BitOr<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U BinaryOr(const U& lhs, const U& rhs) noexcept {
    return Base::BinaryOr(lhs, rhs);
  }

};

template <class T>
class DefaultOr {
public:

  static constexpr bool exists = true;

  static constexpr T BinaryOr(const T& lhs, const T& rhs) noexcept {
    return lhs | rhs;
  }

};

template <class T>
constexpr inline T BinaryOr(const T& lhs, const T& rhs) noexcept {
  return BitOr<T>::BinaryOr(lhs, rhs);
}

}

#pragma clang diagnostic pop