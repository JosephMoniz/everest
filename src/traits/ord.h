#ifndef TRAITOROUS_TRAITS_ORD
#define TRAITOROUS_TRAITS_ORD 1

enum Ordering {
  LESS,
  EQUAL,
  GREATER
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
constexpr T cmp(const T& lhs, const T& rhs) noexcept {
  return ord<T>::cmp(lhs, rhs);
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr T min(const T& lhs, const T& rhs) noexcept {
  return ord<T>::min(lhs, rhs);
}

template <class T, class = typename std::enable_if<ord<T>::exists>::type>
constexpr T max(const T& lhs, const T& rhs) noexcept {
  return ord<T>::max(lhs, rhs);
}

#endif
