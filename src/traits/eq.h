#ifndef TRAITOROUS_TRAITS_EQ
#define TRAITOROUS_TRAITS_EQ 1

namespace traitorous {

template <class T>
struct eq {
  // bool equals()
  static constexpr bool exists = false;
};

template <class T>
struct default_eq {
  static constexpr bool equals(const T& lhs, const T& rhs) noexcept {
    return lhs == rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<eq<T>::exists>::type>
constexpr inline bool equals(const T& lhs, const T& rhs) noexcept {
  return eq<T>::equals(lhs, rhs);
}

template <class T, class = typename std::enable_if<eq<T>::exists>::type>
constexpr inline bool operator==(const T& lhs, const T& rhs) noexcept {
  return eq<T>::equals(lhs, rhs);
}

template <class T, class = typename std::enable_if<eq<T>::exists>::type>
constexpr inline bool operator!=(const T& lhs, const T& rhs) noexcept {
  return eq<T>::equals(lhs, rhs) == false;
}

}

#endif
