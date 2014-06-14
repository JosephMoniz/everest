#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

namespace traitorous {

template <class T>
struct functor {
  // map()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class A,
          class B,
          class = typename std::enable_if<functor<F<A>>::exists>::type>
constexpr F<B> map(std::function<B(const A&)> f, const F<B>& n) noexcept {
  return functor<F<A>>::map(f, n);
}

}

#endif
