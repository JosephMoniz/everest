#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Negation {

  typedef Negation<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr U Negate(const U& n) noexcept {
    return Base::Negate(n);
  }

};

template <class T>
class DefaultNegation {
public:

  static constexpr bool exists = true;

  static constexpr T Negate(const T& n) noexcept {
    return -n;
  }

};

template <class T>
constexpr T Negate(const T& n) noexcept {
  return Negation<T>::Negate(n);
}

}

#pragma clang diagnostic pop