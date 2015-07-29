#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

#include <functional>
#include <type_traits>

namespace traitorous {

template <class T>
struct functor {
  // map()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class Fn,
          class A,
          class B = typename std::result_of<Fn(A)>::type,
          class   = typename std::enable_if<functor<F<A>>::exists>::type>
constexpr inline F<B> map(Fn f, const F<A>& n) noexcept {
  return functor<F<A>>::map(f, n);
}

template <template <class, class> class F,
  class Fn,
  class A,
  class B,
  class R = typename std::result_of<Fn(B)>::type,
  class   = typename std::enable_if<functor<F<A, B>>::exists>::type>
constexpr inline F<A, R> map(Fn f, const F<A, B>& n) noexcept {
  return functor<F<A, B>>::map(f, n);
}

}

#endif
