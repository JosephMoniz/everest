#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <functional>

namespace everest {

template <class T>
class Foldable final {

    typedef Foldable<T> Base;

public:

  static constexpr bool exists = false;

  static T Fold(const T& n) noexcept {
    return Base::Fold(n);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const T& n) noexcept {
    return Base::FoldMap(f, n);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const T& n) noexcept {
    return Base::FoldR(f, init, n);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const T& n) noexcept {
    return Base::FoldL(f, init, n);
  }

};

template <class F>
auto Fold(const F& container) noexcept -> decltype(Foldable<F>::Fold(container)) {
  static_assert(Foldable<F>::exists, "T does not implement Foldable");
  return Foldable<F>::Fold(container);
}

template <class Fn, class F>
auto FoldMap(Fn f, const F& container) noexcept -> decltype(Foldable<F>::FoldMap(f, container)) {
  static_assert(Foldable<F>::exists, "T does not implement Foldable");
  return Foldable<F>::FoldMap(f, container);
}

template <class F, class Fn, class B>
B FoldR(Fn f, const B& init, const F& container) noexcept {
  static_assert(Foldable<F>::exists, "T does not implement Foldable");
  return Foldable<F>::FoldR(f, init, container);
}

template <class F, class Fn, class B>
B FoldL(Fn f, const B& init, const F& container) noexcept {
  static_assert(Foldable<F>::exists, "T does not implement Foldable");
  return Foldable<F>::FoldL(f, init, container);
}

}

#pragma clang diagnostic pop
