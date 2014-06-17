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
constexpr F<B> map(Fn f, const F<A>& n) noexcept {
  return functor<F<A>>::map(f, n);
}

}

#endif
