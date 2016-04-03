#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class Ord<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const SharedArray<T, S> &lhs, const SharedArray<T, S> &rhs) noexcept {
    return Ord<Array<T, S>>::Compare(*lhs.Pointer(), *rhs.Pointer());
  }

  template<size_t Rs>
  static constexpr Ordering Compare(const SharedArray<T, S> &lhs,
                                    const SharedArray<T, Rs> &rhs) noexcept
  {
    return Ord<Array<T, S>>::Compare(*lhs.Pointer(), *rhs.Pointer());
  }

  static constexpr const SharedArray<T, S>& Min(const SharedArray<T, S> &lhs,
                                                const SharedArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
           ? rhs
           : lhs;
  }

  static constexpr const SharedArray<T, S>& Max(const SharedArray<T, S> &lhs,
                                                const SharedArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
           ? rhs
           : lhs;
  }

};

}
