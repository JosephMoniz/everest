#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_ORD_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_ORD_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T, size_t S>
class Ord<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const LocalArray<T, S> &lhs,
                          const LocalArray<T, S> &rhs) noexcept
  {
    for (size_t i = 0; i < S; i ++) {
      switch(Ord<T>::Compare(lhs.pointer()[i], rhs.pointer()[i])) {
        case LESS:    return LESS;
        case GREATER: return GREATER;
        case EQUAL:   continue;
      }
    }
    return EQUAL;
  }

  template<size_t Rs>
  static constexpr Ordering Compare(const LocalArray<T, S> &lhs,
                                    const LocalArray<T, Rs> &rhs) noexcept
  {
    return (S > Rs)
       ? GREATER
       : LESS;
  }

  static constexpr const LocalArray<T, S>& Min(const LocalArray<T, S> &lhs,
                                               const LocalArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const LocalArray<T, S>& Max(const LocalArray<T, S> &lhs,
                                               const LocalArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
       ? rhs
       : lhs;
  }

};

}

#endif
