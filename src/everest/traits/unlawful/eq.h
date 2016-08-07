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

  static bool Equals(const T& lhs, const T& rhs) noexcept {
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
bool Equals(const T& lhs, const T& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
bool Equals(const T* lhs, const T* rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
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
Predicate<const T&> Equals(const T& lhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return [&](const T& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T>
bool NotEquals(const T& lhs, const T& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return !Eq<T>::Equals(lhs, rhs);
}

template <class T>
bool NotEquals(const T* lhs, const T* rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
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
Predicate<const T&> NotEquals(const T& lhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return [&](const T& rhs) {
    return !Eq<T>::Equals(lhs, rhs);
  };
}

template <class T>
bool operator==(const T& lhs, const T& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return Eq<T>::Equals(lhs, rhs);
}

template <class T>
bool operator!=(const T& lhs, const T& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return !Eq<T>::Equals(lhs, rhs);
}

// These are the cases for Eq for comparing different types
//
template <class T, class U>
bool Equals(const T& lhs, const U& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
Predicate<const U&> Equals(const T& lhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return [&](const U& rhs) {
    return Eq<T>::Equals(lhs, rhs);
  };
}

template <class T, class U>
bool operator==(const T& lhs, const U& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return Eq<T>::Equals(lhs, rhs);
}

template <class T, class U>
bool operator!=(const T& lhs, const U& rhs) noexcept {
  static_assert(Eq<T>::exists, "T does not implement Eq");
  return !Eq<T>::Equals(lhs, rhs);
}

}

#pragma clang diagnostic pop
