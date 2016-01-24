#ifndef TRAITOROUS_TRAITS_DROPPABLE
#define TRAITOROUS_TRAITS_DROPPABLE 1

#include <functional>

namespace traitorous {

template <class T>
struct droppable {
  // T drop()
  // T dropWhile()
  static constexpr bool exists = false;
};

template <class T,
          class = typename std::enable_if<droppable<T>::exists>::type>
constexpr inline T drop(const T& n, unsigned int s) noexcept {
  return droppable<T>::drop(n, s);
}

template <template <class> class F,
          class T,
          class = typename std::enable_if<droppable<F<T>>::exists>::type>
constexpr inline F<T> drop_while(const F<T>& n, std::function<bool(const T&)> p) noexcept {
  return droppable<F<T>>::drop_while(n, p);
}

}

#endif
