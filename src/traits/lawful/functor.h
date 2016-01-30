#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

#include <functional>
#include <type_traits>

namespace traitorous {

template <template<class> class F, class T>
class Functor {

  typedef Functor<F, T> Base;

public:

  static constexpr bool exists = false;

  template <class Fn, class B = typename std::result_of<Fn(T)>::type>
  static constexpr F<B> Map(Fn f, const F<T>& n) noexcept {
    return Base::Map(f, n);
  }

};

template <template<class> class F,
          class Fn,
          class A,
          class B = typename std::result_of<Fn(A)>::type>
constexpr inline F<B> Map(Fn f, const F<A>& n) noexcept {
  return Functor<F, A>::Map(f, n);
}

}

#endif

#pragma clang diagnostic pop