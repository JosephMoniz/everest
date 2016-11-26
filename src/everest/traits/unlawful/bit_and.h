#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class BitAnd final {

  typedef BitAnd<T> Base;

public:

  static constexpr bool exists = false;

  static T BinaryAnd(const T& lhs, const T& rhs) noexcept {
    static_assert(exists, "T does not implement BitAnd");
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
  static_assert(BitAnd<T>::exists, "T does not implement BitAnd");
  return BitAnd<T>::BinaryAnd(lhs, rhs);
}

}

#pragma clang diagnostic pop