#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/types/string.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

enum class Ordering {
  LESS,
  EQUAL,
  GREATER
};

template<>
class Shows<Ordering> {
public:

  static constexpr bool exists = true;

  static String Show(Ordering n) noexcept {
    switch(n) {
      case Ordering::LESS:    return String("LESS");
      case Ordering::EQUAL:   return String("EQUAL");
      case Ordering::GREATER: return String("GREATER");
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
       ? Ordering::LESS
       : (lhs > rhs)
         ? Ordering::GREATER
         : Ordering::EQUAL;
  }

  static constexpr int Min(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static constexpr int Max(const T& lhs, const T& rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS) ? rhs : lhs;
  }

};

// These are for the case of comparing the same types
//
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
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T>
constexpr inline bool operator>(const T& lhs, const T& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

// These are the cases for comparing different types
//
template <class T, class U>
constexpr inline Ordering Compare(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs);
}

template <class T, class U>
constexpr inline T Min(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Min(lhs, rhs);
}

template <class T, class U>
constexpr inline T Max(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Max(lhs, rhs);
}

template <class T, class U>
constexpr inline bool operator<(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::LESS;
}

template <class T, class U>
constexpr inline bool operator>(const T& lhs, const U& rhs) noexcept {
  return Ord<T>::Compare(lhs, rhs) == Ordering::GREATER;
}

}

#pragma clang diagnostic pop
