#pragma once

#include <cstddef>
#include <everest/functions/types.h>

namespace everest {

template <class T>
class MutableDrop {

  typedef MutableDrop<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T& DropInPlace(size_t s, T& n) noexcept {
    return Base::DropInPlace(s, n);
  }

  template <template <class> class F>
  static constexpr F<T>& DropInPlaceWhile(Predicate<const T&> p, F<T>& n) noexcept {
    return Base::DropInPlaceWhile(p, n);
  }

};

template <class T>
constexpr T& DropInPlace(size_t s, T& n) noexcept {
  return MutableDrop<T>::DropInPlace(s, n);
}

template <template <class> class F, class T>
constexpr F<T>& DropWhile(Predicate<const T&> p, F<T>& n) noexcept {
  return MutableDrop<F<T>>::DropInPlaceWhile(p, n);
}

}