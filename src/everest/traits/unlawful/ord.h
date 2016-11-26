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
  static Ordering Compare(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement Ord");
    return Base::Compare(lhs, rhs);
  }

  template <class U>
  static U Min(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement Ord");
    return Base::Min(lhs, rhs);
  }

  template <class U>
  static U Max(const U& lhs, const U& rhs) noexcept {
    static_assert(exists, "T does not implement Ord");
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
Ordering Compare(const T& lhs, const T& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs);
}

template <class T>
auto Min(const T& lhs, const T& rhs) noexcept -> decltype(Ord<T>::Min(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Min(lhs, rhs);
}

template <class T>
auto Min(T& lhs, T& rhs) noexcept -> decltype(Ord<T>::Min(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Min(lhs, rhs);
}

template <class T>
auto Max(const T& lhs, const T& rhs) noexcept -> decltype(Ord<T>::Max(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Max(lhs, rhs);
}

template <class T>
auto Max(T& lhs, T& rhs) noexcept -> decltype(Ord<T>::Max(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Max(lhs, rhs);
}

template <class T>
bool operator<(const T& lhs, const T& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T>
bool operator>(const T& lhs, const T& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

// These are the cases for comparing different types
//
template <class T, class U>
Ordering Compare(const T& lhs, const U& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs);
}

template <class T, class U>
auto Min(const T& lhs, const U& rhs) noexcept -> decltype(Ord<T>::Min(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Min(lhs, rhs);
}

template <class T, class U>
auto Max(const T& lhs, U& rhs) noexcept -> decltype(Ord<T>::Max(lhs, rhs)) {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Max(lhs, rhs);
}

template <class T, class U>
bool operator<(const T& lhs, const U& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T, class U>
bool operator>(const T& lhs, const U& rhs) noexcept {
  static_assert(Ord<T>::exists, "T does not implement Ord");
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

}

#pragma clang diagnostic pop
