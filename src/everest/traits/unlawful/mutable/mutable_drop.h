#pragma once

#include <cstddef>
#include <everest/functions/types.h>

namespace everest {

template <class T>
class MutableDrop {

  typedef MutableDrop<T> Base;

public:

  static constexpr bool exists = false;

  static T& DropInPlace(size_t s, T& n) noexcept {
    return Base::DropInPlace(s, n);
  }

  template <template <class> class F>
  static F<T>& DropInPlaceWhile(Predicate<const T&> p, F<T>& n) noexcept {
    return Base::DropInPlaceWhile(p, n);
  }

};

template <class T>
T& DropInPlace(size_t s, T& n) noexcept {
  static_assert(MutableDrop<T>::exists, "T does not implement MutableDrop");
  return MutableDrop<T>::DropInPlace(s, n);
}

template <template <class> class F, class T>
F<T>& DropWhile(Predicate<const T&> p, F<T>& n) noexcept {
  static_assert(MutableDrop<T>::exists, "T does not implement MutableDrop");
  return MutableDrop<F<T>>::DropInPlaceWhile(p, n);
}

}