#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_BITAND
#define TRAITOROUS_TRAITS_BITAND 1

namespace traitorous {

template <class T>
class BitAnd {

  typedef BitAnd<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T BinaryAnd(const T& lhs, const T& rhs) noexcept {
    return Base::BinaryAnd(lhs, rhs);
  }

};

template <class T>
class DefaultAnd {
public:

  static constexpr bool exists = true;

  static constexpr T BinaryAnd(const T& lhs, const T& rhs) noexcept {
    return lhs & rhs;
  }

};

template <class T>
constexpr inline T BinaryAnd(const T& lhs, const T& rhs) noexcept {
  return BitAnd<T>::BinaryAnd(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop