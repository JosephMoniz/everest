#ifndef TRAITOROUS_TRAITS_SUBTRACT
#define TRAITOROUS_TRAITS_SUBTRACT 1

namespace traitorous {

template <class T>
struct subtractable {
  // T subtract()
  static constexpr bool exists = false;
};

template <class T>
struct default_subtract {
  static constexpr T subtract(const T& lhs, const T& rhs) noexcept {
    return lhs - rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<subtractable<T>::exists>::type>
constexpr T subtract(const T& lhs, const T& rhs) noexcept {
  return subtractable<T>::subtract(lhs, rhs);
}

template <class T, class = typename std::enable_if<subtractable<T>::exists>::type>
constexpr T operator-(const T& lhs, const T& rhs) noexcept {
  return subtractable<T>::subtract(lhs, rhs);
}

}

#endif
