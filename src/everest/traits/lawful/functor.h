#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class F>
class Functor final {

  typedef Functor<F> Base;

public:

  static constexpr bool exists = false;

  template <class Fn, class B>
  static constexpr B Map(Fn f, const F& n) noexcept {
    return Base::Map(f, n);
  }

};

template <class Fn, class A>
auto Map(Fn f, A&& n) noexcept -> decltype(Functor<A>::Map(f, std::forward<A>(n))) {
  static_assert(Functor<A>::exists, "T does not implement Functor");
  return Functor<A>::Map(f, std::forward<A>(n));
}

}

#pragma clang diagnostic pop