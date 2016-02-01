#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_FOLDABLE
#define TRAITOROUS_TRAITS_FOLDABLE 1

#include <functional>
#include <memory>

#include "monoid.h"

namespace traitorous {

template <class T>
class Foldable {

    typedef Foldable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T Fold(const T& n) noexcept {
    return Base::Fold(n);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const T& n) noexcept {
    return Base::FoldMap(f, n);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const T& n) noexcept {
    return Base::FoldR(f, init, n);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const T& n) noexcept {
    return Base::FoldL(f, init, n);
  }

};

template <class F>
constexpr inline auto Fold(const F& container) noexcept {
  return Foldable<F>::Fold(container);
}

template <class Fn, class F>
constexpr inline auto FoldMap(Fn f, const F& container) noexcept {
  return Foldable<F>::FoldMap(f, container);
}

template <template<class> class F,
          class T,
          class Fn,
          class B>
constexpr inline B FoldR(Fn f,
                         const B& init,
                         const F<T>& container) noexcept
{
  return Foldable<F<T>>::FoldR(f, init, container);
}

template <template<class> class F,
          class T,
          class Fn,
          class B>
constexpr inline B FoldL(Fn f,
                         const B& init,
                         const F<T>& container) noexcept
{
  return Foldable<F<T>>::FoldL(f, init, container);
}

}

#endif

#pragma clang diagnostic pop