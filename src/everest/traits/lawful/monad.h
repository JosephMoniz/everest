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
  static B FlatMap(Fn f, const F& m) noexcept {
    static_assert(exists, "T does not implement Monad");
    return Base::FlatMap(f, m);
  }

  template <class B>
  static B Then(const F& m, const B& n) noexcept {
    static_assert(exists, "T does not implement Monad");
    return Base::Then(m, n);
  }

};

template <class Fn, class F>
auto FlatMap(Fn f, const F& m) noexcept -> decltype(Monad<F>::FlatMap(f, m)) {
  static_assert(Monad<F>::exists, "T does not implement Monad");
  return Monad<F>::FlatMap(f, m);
}

template <class F, class B>
B Then(const F& a, const B& b) noexcept {
  static_assert(Monad<F>::exists, "T does not implement Monad");
  return Monad<F>::Then(a, b);
}

}

#pragma clang diagnostic pop