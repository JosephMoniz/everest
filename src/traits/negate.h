#ifndef TRAITOROUS_TRAITS_NEGATE
#define TRAITOROUS_TRAITS_NEGATE 1

#include <functional>

namespace traitorous {

template <class T>
struct negation {
  // int not()
  static constexpr bool exists = false;
};

template <class T>
struct default_negation {
  static constexpr T negate(const T& n) noexcept { return std::negate<T>()(n); }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<negation<T>::exists>::type>
constexpr inline T negate(const T& n) noexcept {
  return negation<T>::negate(n);
}

}

#endif
