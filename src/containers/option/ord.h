#ifndef TRAITOROUS_CONTAINERS_OPTION_ORD
#define TRAITOROUS_CONTAINERS_OPTION_ORD

#include "containers/option.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template<class T>
class Ord<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return Ord<LocalOption<T>>::Compare(*lhs.Pointer(), *rhs.Pointer());
  }

  static constexpr const Option<T>& Min(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Option<T>& Max(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

}

#endif
