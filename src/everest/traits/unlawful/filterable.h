#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <functional>

namespace everest {

template <class T>
class Filterable {

  typedef Filterable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class P>
  static T Filter(P p, const F& n) noexcept {
    return Base::Filter(p, n);
  }

};

template <class F, class P>
auto Filter(P p, F&& n) noexcept -> decltype(Filterable<F>::Filter(p, std::forward<F>(n))) {
  return Filterable<F>::Filter(p, std::forward<F>(n));
}

}

#pragma clang diagnostic pop