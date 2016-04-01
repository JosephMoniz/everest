#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <functional>

namespace traitorous {

template <class T>
struct Filterable {

  typedef Filterable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class P>
  static constexpr inline F Filter(P p, const F& n) noexcept {
    return Base::Filter(p, n);
  }

};

template <class F, class P>
constexpr inline F Filter(P p, const F& n) noexcept {
  return Filterable<F>::Filter(p, n);
}

}

#pragma clang diagnostic pop