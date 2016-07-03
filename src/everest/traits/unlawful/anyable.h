#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Anyable {

  typedef Anyable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class P, class U>
  static constexpr bool Any(P p, const F& n) noexcept {
    return Base::Any(p, n);
  }

};

template <class F, class P>
constexpr bool Any(P p, const F& n) noexcept {
  return Anyable<F>::Any(p, n);
}

template <class F, class P>
constexpr bool Any(P p, F&& n) noexcept {
  return Anyable<F>::Any(p, std::forward<F>(n));
}

}

#pragma clang diagnostic pop