#ifndef TRAITOROUS_TRAITS_SEMIGROUP
#define TRAITOROUS_TRAITS_SEMIGROUP 1

namespace traitorous {

template <class T>
struct semigroup {
  // T add()
  static constexpr bool exists = false;
};

template <class T>
struct default_semigroup {
  static constexpr T add(const T& lhs, const T& rhs) noexcept {
    return lhs + rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<semigroup<T>::exists>::type>
constexpr T add(const T& lhs, const T& rhs) noexcept {
  return semigroup<T>::add(lhs, rhs);
}

template <class T, class = typename std::enable_if<semigroup<T>::exists>::type>
constexpr T operator+(const T& lhs, const T& rhs) noexcept {
  return semigroup<T>::add(lhs, rhs);
}

}

#endif
