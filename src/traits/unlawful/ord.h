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
struct shows<Ordering> {
  static std::string show(Ordering n) noexcept {
    switch(n) {
      case LESS:    return std::string("LESS");
      case EQUAL:   return std::string("EQUAL");
      case GREATER: return std::string("GREATER");
      default:      return std::string("UNKNOWN");
    }
  }
  static constexpr bool exists = true;
};

template <class T>
struct ord {
  // Ordering cmp()
  // T min()
  // T max()
  static constexpr bool exists = false;
};

template <class T>
struct default_ord {
  static constexpr Ordering cmp(const T& lhs, const T& rhs) noexcept {
    return (lhs < rhs)
             ? LESS
             : (lhs > rhs)
                 ? GREATER
                 : EQUAL;
  }
  static constexpr int min(const T& lhs, const T& rhs) noexcept {
    return (ord<T>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr int max(const T& lhs, const T& rhs) noexcept {
    return (ord<T>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};


template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr inline Ordering cmp(const T& lhs, const T& rhs) noexcept {
  return ord<T>::cmp(lhs, rhs);
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr inline T min(const T& lhs, const T& rhs) noexcept {
  return ord<T>::min(lhs, rhs);
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr inline T max(const T& lhs, const T& rhs) noexcept {
  return ord<T>::max(lhs, rhs);
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr inline bool operator<(const T& lhs, const T& rhs) noexcept {
  return ord<T>::cmp(lhs, rhs) == LESS;
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr inline bool operator>(const T& lhs, const T& rhs) noexcept {
  return ord<T>::cmp(lhs, rhs) == GREATER;
}

}

#endif
