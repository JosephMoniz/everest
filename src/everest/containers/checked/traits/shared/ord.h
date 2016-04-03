#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template<class E, class T>
class Ord<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Ord<Checked<E, T>>::Compare(*lhs, *rhs);
  }

  static constexpr const SharedChecked<E, T>& Min(const SharedChecked<E, T>& lhs,
                                                  const SharedChecked<E, T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const SharedChecked<E, T>& Max(const SharedChecked<E, T>& lhs,
                                                  const SharedChecked<E, T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}