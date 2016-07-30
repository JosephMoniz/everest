#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/traits/unlawful/ord/ordering.h>

namespace everest {

template <class T>
class Ord {

  typedef Ord<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr Ordering Compare(const U& lhs, const U& rhs) noexcept {
    return Base::Compare(lhs, rhs);
  }

  template <class U>
  static constexpr U Min(const U& lhs, const U& rhs) noexcept {
    return Base::Min(lhs, rhs);
  }

  template <class U>
  static constexpr U Max(const U& lhs, const U& rhs) noexcept {
    return Base::Max(lhs, rhs);
  }

};

template <class T>
class DefaultOrd {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const T& lhs, const T& rhs) noexcept {
    return (lhs < rhs)
       ? Ordering::LESS
       : (lhs > rhs)
         ? Ordering::GREATER
         : Ordering::EQUAL;
  }

  static T Min(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static T Max(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

// These are for the case of comparing the same types
//
template <class T>
constexpr Ordering Compare(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs);
}

template <class T>
constexpr T Min(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Min(lhs, rhs);
}

template <class T>
constexpr T Max(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Max(lhs, rhs);
}

template <class T>
constexpr bool operator<(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T>
constexpr bool operator>(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

// These are the cases for comparing different types
//
template <class T, class U>
constexpr Ordering Compare(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs);
}

template <class T, class U>
constexpr T Min(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Min(lhs, rhs);
}

template <class T, class U>
constexpr T Max(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Max(lhs, rhs);
}

template <class T, class U>
constexpr bool operator<(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T, class U>
constexpr bool operator>(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

}

#pragma clang diagnostic pop
