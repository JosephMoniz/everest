#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

template <class T>
struct functor {
  // map()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class A,
          class B,
          class = typename std::enable_if<functor<F<A>>::exists>::type>
constexpr F<B> map(const F<B>& n, std::function<B(const A&)> f) noexcept {
  return functor<F<A>>::map(n, f);
}

#endif
