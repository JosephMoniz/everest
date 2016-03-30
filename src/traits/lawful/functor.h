#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <functional>
#include <type_traits>

namespace traitorous {

template <class F>
class Functor {

  typedef Functor<F> Base;

public:

  static constexpr bool exists = false;

  template <class Fn, class B>
  static constexpr B Map(Fn f, const F& n) noexcept {
    return Base::Map(f, n);
  }

};

template <class Fn, class A>
auto Map(Fn f, const A& n) noexcept -> decltype(Functor<A>::Map(f, n)) {
  return Functor<A>::Map(f, n);
}

}

#pragma clang diagnostic pop