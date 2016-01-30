#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_ORD
#define TRAITOROUS_TRAITS_ORD 1

#include "traits/unlawful/show.h"

namespace traitorous {

enum Ordering {
  LESS,
  EQUAL,
  GREATER
};

template<>
class Shows<Ordering> {
public:

  static constexpr bool exists = true;

  static std::string Show(Ordering n) noexcept {
    switch(n) {
      case LESS:    return std::string("LESS");
      case EQUAL:   return std::string("EQUAL");
      case GREATER: return std::string("GREATER");
      default:      return std::string("UNKNOWN");
    }
  }

};

template <class T>
class Ord {

  typedef Ord<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline Ordering Compare(const U& lhs, const U& rhs) noexcept {
    return Base::Compare(lhs, rhs);
  }

  template <class U>
  static constexpr inline U Min(const U& lhs, const U& rhs) noexcept {
    return Base::Min(lhs, rhs);
  }

  template <class U>
  static constexpr inline U Max(const U& lhs, const U& rhs) noexcept {
    return Base::Max(lhs, rhs);
  }

};

template <class T>
class DefaultOrd {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const T& lhs, const T& rhs) noexcept {
    return (lhs < rhs)
       ? LESS
       : (lhs > rhs)
         ? GREATER
         : EQUAL;
  }

  static constexpr int Min(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == GREATER)
       ? rhs
       : lhs;
  }

  static constexpr int Max(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == LESS) ? rhs : lhs;
  }

};


template <class T>
constexpr inline Ordering Compare(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs);
}

template <class T>
constexpr inline T Min(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Min(lhs, rhs);
}

template <class T>
constexpr inline T Max(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Max(lhs, rhs);
}

template <class T>
constexpr inline bool operator<(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == LESS;
}

template <class T>
constexpr inline bool operator>(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == GREATER;
}

}

#endif

#pragma clang diagnostic pop