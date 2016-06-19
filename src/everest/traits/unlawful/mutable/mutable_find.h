#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableFind {

  typedef MutableFind<T> Base;

public:

  static constexpr bool exists = false;

  template <class P, class U>
  static U& FindInPlace(P p, T& n) noexcept {
    return Base::FindInPlace(p, n);
  }

};

template <class F, class P>
auto FindInPlace(P p, F& n) noexcept -> decltype(MutableFind<F>::FindInPlace(p, n)) {
  return MutableFind<F>::FindInPlace(p, n);
}

}

#pragma clang diagnostic pop