#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace traitorous {

template <class T>
class MonadPlus {

  typedef MonadPlus<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr T MPlus(const T& lhs, const T& rhs) noexcept {
    return Base::MPlus(lhs, rhs);
  }

};

template <class M>
constexpr inline M MPlus(const M& a, const M& b) noexcept {
  return MonadPlus<M>::MPlus(a, b);
}

}

#pragma clang diagnostic pop