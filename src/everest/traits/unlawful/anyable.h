#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Anyable final {

  typedef Anyable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class P, class U>
  static bool Any(P p, const F& n) noexcept {
    static_assert(exists, "T does not implement Anyable");
    return Base::Any(p, n);
  }

};

template <class F, class P>
bool Any(P p, const F& n) noexcept {
  static_assert(Anyable<F>::exists, "T does not implement Anyable");
  return Anyable<F>::Any(p, n);
}

template <class F, class P>
bool Any(P p, F&& n) noexcept {
  static_assert(Anyable<F>::exists, "T does not implement Anyable");
  return Anyable<F>::Any(p, std::forward<F>(n));
}

}

#pragma clang diagnostic pop