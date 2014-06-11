#ifndef TRAITOROUS_TRAITS_BITXOR
#define TRAITOROUS_TRAITS_BITXOR 1

template <class T>
struct bit_xor {
  // T xor()
  static constexpr bool exists = false;
};

template <class T>
struct default_xor {
  static constexpr bool apply(const T& lhs, const T& rhs) noexcept {
    return lhs & rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<bit_xor<T>::exists>::type>
constexpr bool b_xor(const T& lhs, const T& rhs) noexcept {
  return bit_xor<T>::apply(lhs, rhs);
}

#endif
