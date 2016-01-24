#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_FOLDABLE
#define TRAITOROUS_TRAITS_FOLDABLE 1

#include <functional>
#include <memory>

#include "monoid.h"

namespace traitorous {

template <class T>
class foldable {

    typedef foldable<T> base;

public:

  static constexpr T fold(const T& n) noexcept {
    return base::fold(n);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M fold_map(Fn f, const T& n) noexcept {
    return base::fold_map(f, n);
  }

  template <class Fn, class B>
  static constexpr B foldr(Fn f, const B& init, const T& n) noexcept {
    return base::foldr(f, init, n);
  }

  template <class Fn, class B>
  static constexpr B foldl(Fn f, const B& init, const T& n) noexcept {
    return base::foldl(f, init, n);
  }

  static constexpr bool exists = false;

};

template <template<class> class F, class M>
constexpr inline M fold(const F<M>& container) noexcept {
  return foldable<F<M>>::fold(container);
}

template <template<class> class F,
          class A,
          class Fn,
          class M = typename std::result_of<Fn(A)>::type>
constexpr inline M fold_map(Fn f, const F<A>& container) noexcept {
  return foldable<F<A>>::fold_map(f, container);
}

template <template<class> class F,
          class T,
          class Fn,
          class B>
constexpr inline B foldr(Fn f,
                         const B& init,
                         const F<T>& container) noexcept
{
  return foldable<F<T>>::foldr(f, init, container);
}

template <template<class> class F,
          class T,
          class Fn,
          class B>
constexpr inline B foldl(Fn f,
                         const B& init,
                         const F<T>& container) noexcept
{
  return foldable<F<T>>::foldl(f, init, container);
}

}

#endif

#pragma clang diagnostic pop