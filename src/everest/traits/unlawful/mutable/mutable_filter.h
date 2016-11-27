#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableFilter {

  typedef MutableFilter<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class P>
  static F& FilterInPlace(P p, F& n) noexcept {
    return Base::FilterInPlace(p, n);
  }

};

template <class F, class P>
F& FilterInPlace(P p, F& n) noexcept {
  static_assert(MutableFilter<F>::exists, "F does not implement MutableFilter");
  return MutableFilter<F>::FilterInPlace(p, n);
}

}

#pragma clang diagnostic pop