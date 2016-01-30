#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_BITXOR
#define TRAITOROUS_TRAITS_BITXOR 1

namespace traitorous {

template <class T>
class BitXor {

  typedef BitXor<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U BinaryXor(const U& lhs, const U& rhs) noexcept {
    return Base::BinaryXor(lhs, rhs);
  }

};

template <class T>
class DefaultXor {
public:

  static constexpr bool exists = true;

  static constexpr T BinaryXor(const T& lhs, const T& rhs) noexcept {
    return lhs ^ rhs;
  }

};

template <class T>
constexpr inline T BinaryXor(const T& lhs, const T& rhs) noexcept {
  return BitXor<T>::BinaryXor(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop