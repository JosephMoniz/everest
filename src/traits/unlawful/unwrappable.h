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

template <class F,
          class D,
          class T = typename std::result_of<D()>::type,
          class   = typename std::enable_if<unwrappable<F>::exists>::type>
constexpr inline T get_or_else(D d, const F& f) noexcept {
  return unwrappable<F>::get_or_else(d, f);
}


template <class F,
          class T,
          class = typename std::enable_if<unwrappable<F>::exists>::type>
constexpr inline T get_or_default(const T& f, const F& n) noexcept {
  return unwrappable<F>::get_or_default(f, n);
}

}

#endif
