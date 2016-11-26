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
  static U Negate(const U& n) noexcept {
    static_assert(exists, "T does not implement Negation");
    return Base::Negate(n);
  }

};

template <class T>
class DefaultNegation {
public:

  static constexpr bool exists = true;

  static T Negate(const T& n) noexcept {
    return -n;
  }

};

template <class T>
T Negate(const T& n) noexcept {
  static_assert(Negation<T>::exists, "T does not implement Negation");
  return Negation<T>::Negate(n);
}

}

#pragma clang diagnostic pop