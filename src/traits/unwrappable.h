#ifndef TRAITOROUS_TRAITS_UNWRAPPABLE
#define TRAITOROUS_TRAITS_UNWRAPPABLE 1

#include <functional>

namespace traitorous {

template <class T>
struct unwrappable {
  // get_or_else()
  // get_or_default()
  static constexpr bool exists = false;
};

  template <template <class> class F,
          class T,
          class = typename std::enable_if<unwrappable<F<T>>::exists>::type>
constexpr inline T get_or_else(const F<T>& f, const T& d) noexcept {
  return unwrappable<T>::get_or_else(f, d);
}

template <template <class> class F,
          class T,
          class = typename std::enable_if<unwrappable<F<T>>::exists>::type>
constexpr inline T get_or_default(const F<T>& n, std::function<T()> f) noexcept {
  return unwrappable<F<T>>::get_or_default(n, f);
}

}

#endif
