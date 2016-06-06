#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Ord<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const SharedMutableArray<T, S> &lhs, const SharedMutableArray<T, S> &rhs) noexcept {
    return Ord<MutableArray<T, S>>::Compare(*lhs, *rhs);
  }

  template<size_t Rs>
  static constexpr Ordering Compare(const SharedMutableArray<T, S> &lhs,
                                    const SharedMutableArray<T, Rs> &rhs) noexcept
  {
    return Ord<MutableArray<T, S>>::Compare(*lhs, *rhs);
  }

  static constexpr const SharedMutableArray<T, S>& Min(const SharedMutableArray<T, S> &lhs,
                                                       const SharedMutableArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const SharedMutableArray<T, S>& Max(const SharedMutableArray<T, S> &lhs,
                                                       const SharedMutableArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}
