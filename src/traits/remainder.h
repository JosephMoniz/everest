#ifndef TRAITOROUS_TRAITS_REMAINDER
#define TRAITOROUS_TRAITS_REMAINDER 1

template <class T>
struct modulus {
  // int modulus()
  static constexpr bool exists = false;
};

template <class T>
struct default_modulus {
  static T modulo(const T& lhs, const T& rhs) noexcept { return lhs % rhs; }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<modulus<T>::exists>::type>
constexpr T remainder(const T& lhs, const T& rhs) noexcept {
  return modulus<T>::modulo(lhs, rhs);
}

#endif
