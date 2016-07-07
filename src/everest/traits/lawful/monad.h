#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class F>
class Monad final {

  typedef Monad<F> Base;

public:

  static constexpr bool exists = false;

  template <class Fn, class B = typename std::result_of<Fn(F)>::type>
  static constexpr B FlatMap(Fn f, const F& m) noexcept {
    return Base::FlatMap(f, m);
  }

  template <class B>
  static constexpr B Then(const F& m, const B& n) noexcept {
    return Base::Then(m, n);
  }

};

template <class Fn, class F>
constexpr auto FlatMap(Fn f, const F& m) noexcept {
  return Monad<F>::FlatMap(f, m);
}

template <class F, class B>
constexpr B Then(const F& a, const B& b) noexcept {
  return Monad<F>::Then(a, b);
}

}

#pragma clang diagnostic pop