#ifndef TRAITOROUS_TRAITS_BITOR
#define TRAITOROUS_TRAITS_BITOR 1

namespace traitorous {

template <class T>
struct bit_or {
  // T or()
  static constexpr bool exists = false;
};

template <class T>
struct default_or {
  static constexpr bool apply(const T& lhs, const T& rhs) noexcept {
    return lhs | rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<bit_or<T>::exists>::type>
constexpr inline bool b_or(const T& lhs, const T& rhs) noexcept {
  return bit_or<T>::apply(lhs, rhs);
}

}

#endif
