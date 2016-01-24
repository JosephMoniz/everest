#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

#include <functional>
#include <type_traits>

namespace traitorous {

template <template<class> class F, class T>
class functor {

  typedef functor<F, T> base;

public:

  template <class Fn, class B = typename std::result_of<Fn(T)>::type>
  static constexpr F<B> map(Fn f, const F<T>& n) noexcept {
    return base::map(f, n);
  }

  static constexpr bool exists = false;

};

template <template<class> class F,
          class Fn,
          class A,
          class B = typename std::result_of<Fn(A)>::type>
constexpr inline F<B> map(Fn f, const F<A>& n) noexcept {
  return functor<F, A>::map(f, n);
}

}

#endif

#pragma clang diagnostic pop