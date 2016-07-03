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
auto Drop(size_t s, T&& n) noexcept -> decltype(Droppable<T>::Drop(s, std::forward<T>(n))) {
  return Droppable<T>::Drop(s, std::forward<T>(n));
}

template <class Predicate, class T>
auto DropWhile(Predicate p, T&& n) noexcept -> decltype(Droppable<T>::DropWhile(p, std::forward<T>(n))) {
  return Droppable<T>::DropWhile(p, std::forward<T>(n));
}

}

#pragma clang diagnostic pop
