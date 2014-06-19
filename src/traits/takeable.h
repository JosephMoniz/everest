#ifndef TRAITOROUS_TRAITS_TAKEABLE
#define TRAITOROUS_TRAITS_TAKEABLE 1

#include <functional>

namespace traitorous {

template <class T>
struct takeable {
  // T take()
  // T takeWhile()
  static constexpr bool exists = false;
};

template <class T,
          class = typename std::enable_if<takeable<T>::exists>::type>
constexpr inline T take(const T& n, unsigned int s) noexcept {
  return takeable<T>::take(n, s);
}

template <template <class> class F,
          class T,
          class = typename std::enable_if<takeable<F<T>>::exists>::type>
constexpr inline F<T> take_while(const F<T>& n, std::function<bool(const T&)> p) noexcept {
  return takeable<F<T>>::take_while(n, p);
}

}

#endif
