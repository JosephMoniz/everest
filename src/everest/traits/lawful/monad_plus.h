#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MonadPlus final {

  typedef MonadPlus<T> Base;

public:

  static constexpr bool exists = false;

  static T MPlus(const T& lhs, const T& rhs) noexcept {
    return Base::MPlus(lhs, rhs);
  }

};

template <class M>
M MPlus(const M& a, const M& b) noexcept {
  static_assert(MonadPlus<M>::exists, "T does not implement MonadPlus");
  return MonadPlus<M>::MPlus(a, b);
}

}

#pragma clang diagnostic pop