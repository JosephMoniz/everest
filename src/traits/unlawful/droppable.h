#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_DROPPABLE
#define TRAITOROUS_TRAITS_DROPPABLE 1

#include <functional>

#include "functions/types.h"

namespace traitorous {

template <class T>
struct Droppable {

  typedef Droppable<T> Base;

public:

  static constexpr bool exists = false;

  template <class T>
  static constexpr inline T Drop(const T& n, unsigned int s) noexcept {
    return Base::Drop(n, s);
  }

  template <template <class> class F, class T>
  static constexpr inline F<T> DropWhile(const F<T>& n, Predicate<const T&> p) noexcept {
    return Base::DropWhile(n, p);
  }

};

template <class T>
constexpr inline T Drop(const T& n, unsigned int s) noexcept {
  return Droppable<T>::Drop(n, s);
}

template <template <class> class F, class T>
constexpr inline F<T> DropWhile(const F<T>& n, Predicate<const T&> p) noexcept {
  return Droppable<F<T>>::DropWhile(n, p);
}

}

#endif

#pragma clang diagnostic pop
