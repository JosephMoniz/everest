#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class BitOr {

  typedef BitOr<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static U BinaryOr(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement BitOr");
    return Base::BinaryOr(lhs, rhs);
  }

};

template <class T>
class DefaultOr {
public:

  static constexpr bool exists = true;

  static T BinaryOr(const T& lhs, const T& rhs) noexcept {
    return lhs | rhs;
  }

};

template <class T>
T BinaryOr(const T& lhs, const T& rhs) noexcept {
  static_assert(BitOr<T>::exists, "T does not implement BitOr");
  return BitOr<T>::BinaryOr(lhs, rhs);
}

}

#pragma clang diagnostic pop