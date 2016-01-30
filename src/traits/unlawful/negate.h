#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_NEGATE
#define TRAITOROUS_TRAITS_NEGATE 1

namespace traitorous {

template <class T>
class Negation {

  typedef Negation<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U Negate(const U& n) noexcept {
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
constexpr inline T Negate(const T& n) noexcept {
  return Negation<T>::Negate(n);
}

}

#endif

#pragma clang diagnostic pop