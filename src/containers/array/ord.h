#ifndef TRAITOROUS_CONTAINERS_ARRAY_ORD_H
#define TRAITOROUS_CONTAINERS_ARRAY_ORD_H

#include "containers/array.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T, size_t S>
class Ord<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Array<T, S> &lhs, const Array<T, S> &rhs) noexcept {
    return Ord<LocalArray<T, S>>::Compare(*lhs.Pointer(), *rhs.Pointer());
  }

  template<size_t Rs>
  static constexpr Ordering Compare(const Array<T, S> &lhs,
                                    const Array<T, Rs> &rhs) noexcept
  {
    return Ord<LocalArray<T, S>>::Compare(*lhs.Pointer(), *rhs.Pointer());
  }

  static constexpr const Array<T, S>& Min(const Array<T, S> &lhs,
                                          const Array<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
           ? rhs
           : lhs;
  }

  static constexpr const Array<T, S>& Max(const Array<T, S> &lhs,
                                          const Array<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
           ? rhs
           : lhs;
  }

};

}

#endif
