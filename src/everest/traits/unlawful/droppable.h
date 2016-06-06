#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Droppable {

  typedef Droppable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Drop(size_t s, const T& n) noexcept {
    return Base::Drop(s, n);
  }

  template <template <class> class F>
  static constexpr F<T> DropWhile(Predicate<const T&> p, const F<T>& n) noexcept {
    return Base::DropWhile(p, n);
  }

};

template <class T>
constexpr T Drop(size_t s, const T& n) noexcept {
  return Droppable<T>::Drop(s, n);
}

template <template <class> class F, class T>
constexpr F<T> DropWhile(Predicate<const T&> p, const F<T>& n) noexcept {
  return Droppable<F<T>>::DropWhile(p, n);
}

}

#pragma clang diagnostic pop
