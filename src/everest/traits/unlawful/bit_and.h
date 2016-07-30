#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class BitAnd final {

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

  static T BinaryAnd(const T& lhs, const T& rhs) noexcept {
    return lhs & rhs;
  }

};

template <class T>
T BinaryAnd(const T& lhs, const T& rhs) noexcept {
  return BitAnd<T>::BinaryAnd(lhs, rhs);
}

}

#pragma clang diagnostic pop