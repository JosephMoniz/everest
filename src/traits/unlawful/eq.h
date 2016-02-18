#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_EQ
#define TRAITOROUS_TRAITS_EQ 1

namespace traitorous {

template <class T>
class Eq {

  typedef Eq<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr bool Equals(const T& lhs, const T& rhs) noexcept {
    return Base::Equals(lhs, rhs);
  }

};

template <class T>
class DefaultEq {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const T& lhs, const T& rhs) noexcept {
    return lhs == rhs;
  }

};

// These are the same type Eq cases
//
template <class T>
constexpr inline bool Equals(const T& lhs, const T& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
constexpr inline Predicate<const T&> Equals(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T>
constexpr inline bool operator==(const T& lhs, const T& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator!=(const T& lhs, const T& rhs) noexcept {
  return !Eq<T>::Equals(lhs, rhs);
}

// These are the cases for Eq for comparing different types
//
template <class T, class U>
constexpr inline bool Equals(const T& lhs, const U& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
constexpr inline Predicate<const U&> Equals(const T& lhs) noexcept {
  return [&](const U& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T, class U>
constexpr inline bool operator==(const T& lhs, const U& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
constexpr inline bool operator!=(const T& lhs, const U& rhs) noexcept {
  return !Eq<T>::Equals(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop
