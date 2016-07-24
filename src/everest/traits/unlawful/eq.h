#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/functions/types.h>

namespace everest {

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

  static bool Equals(const T& lhs, const T& rhs) noexcept {
    return lhs == rhs;
  }

};

// These are the same type Eq cases
//
template <class T>
constexpr bool Equals(const T& lhs, const T& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
constexpr bool Equals(const T* lhs, const T* rhs) noexcept {
  if (lhs == nullptr) {
    return rhs == nullptr;
  } else {
    if (rhs == nullptr) {
      return false;
    } else {
      return Eq<T>::Equals(lhs, rhs);
    }
  }
}

template <class T>
constexpr Predicate<const T&> Equals(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T>
constexpr bool NotEquals(const T& lhs, const T& rhs) noexcept {
  return !Eq<T>::Equals(lhs, rhs);
}

template <class T>
constexpr bool NotEquals(const T* lhs, const T* rhs) noexcept {
  if (lhs == nullptr) {
    return rhs != nullptr;
  } else {
    if (rhs == nullptr) {
      return true;
    } else {
      return !Eq<T>::Equals(*lhs, *rhs);
    }
  }
}

template <class T>
constexpr Predicate<const T&> NotEquals(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return !Eq<T>::Equals(lhs, rhs);
  };
}

template <class T>
constexpr bool operator==(const T& lhs, const T& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
constexpr bool operator!=(const T& lhs, const T& rhs) noexcept {
  return !Eq<T>::Equals(lhs, rhs);
}

// These are the cases for Eq for comparing different types
//
template <class T, class U>
constexpr bool Equals(const T& lhs, const U& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
constexpr Predicate<const U&> Equals(const T& lhs) noexcept {
  return [&](const U& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T, class U>
constexpr bool operator==(const T& lhs, const U& rhs) noexcept {
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
constexpr bool operator!=(const T& lhs, const U& rhs) noexcept {
  return !Eq<T>::Equals(lhs, rhs);
}

}

#pragma clang diagnostic pop
