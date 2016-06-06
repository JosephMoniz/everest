#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Modulus {

  typedef Modulus<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr U Modulo(const U& lhs, const U& rhs) noexcept {
    return Base::Modulo(lhs, rhs);
  }

};

template <class T>
class DefaultModulus {
public:

  static constexpr bool exists = true;

  static T Modulo(const T& lhs, const T& rhs) noexcept {
    return lhs % rhs;
  }

};

template <class T>
constexpr T Remainder(const T& lhs, const T& rhs) noexcept {
  return Modulus<T>::Modulo(lhs, rhs);
}

}

#pragma clang diagnostic pop