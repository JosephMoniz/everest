#ifndef TRAITOROUS_TRAITS_MULTIPLY
#define TRAITOROUS_TRAITS_MULTIPLY 1

namespace traitorous {

template <class T>
struct multipliable {
  // T multiply()
  static constexpr bool exists = false;
};

template <class T>
struct default_multipliable {
  static T multiply(const T& lhs, const T& rhs) noexcept { return lhs * rhs; }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<multipliable<T>::exists>::type>
constexpr inline T multiply(const T& lhs, const T& rhs) noexcept {
  return multipliable<T>::multiply(lhs, rhs);
}

template <class T, class = typename std::enable_if<multipliable<T>::exists>::type>
constexpr inline T operator*(const T& lhs, const T& rhs) noexcept {
  return multipliable<T>::multiply(lhs, rhs);
}

}

#endif
