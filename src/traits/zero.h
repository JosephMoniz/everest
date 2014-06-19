#ifndef TRAITOROUS_TRAITS_ZERO
#define TRAITOROUS_TRAITS_ZERO 1

namespace traitorous {

template <class T>
struct zero_val {
  // T zero()
  static constexpr bool exists = false;
};

template <class T>
struct default_zero_val {
  static constexpr T zero() noexcept { return T{}; }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<zero_val<T>::exists>::type>
constexpr inline T zero() noexcept {
  return zero_val<T>::zero();
}

}

#endif
