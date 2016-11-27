#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>

namespace everest {

template <class F>
class Service final {

  typedef Service<F> Base;

public:

  static constexpr bool exists = false;

  template <class A, class B>
  static constexpr B Call(const F& f, const A& a) noexcept {
    return Base::Call(f, a);
  }

};

template <class Fn, class A>
auto Call(Fn f, A&& n) noexcept -> decltype(Service<A>::Call(f, std::forward<A>(n))) {
  static_assert(Service<A>::exists, "T does not implement Service");
  return Service<Fn>::Call(f, std::forward<A>(n));
}

}

#pragma clang diagnostic pop