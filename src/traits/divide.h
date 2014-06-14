#ifndef TRAITOROUS_TRAITS_DIVIDE
#define TRAITOROUS_TRAITS_DIVIDE 1

namespace traitorous {

template <class T>
struct dividable {
  // T divide()
  static constexpr bool exists = false;
};

template <class T>
struct default_dividable {
  static T divide(const T& lhs, const T& rhs) noexcept { return lhs / rhs; }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<dividable<T>::exists>::type>
constexpr T divide(const T& lhs, const T& rhs) noexcept {
  return dividable<T>::divide(lhs, rhs);
}

}

#endif
