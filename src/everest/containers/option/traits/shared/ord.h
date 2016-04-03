#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
class Ord<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const SharedOption<T> &lhs, const SharedOption<T> &rhs) noexcept {
    return Ord<Option<T>>::Compare(*lhs, *rhs);
  }

  static constexpr const SharedOption<T>& Min(const SharedOption<T> &lhs, const SharedOption<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const SharedOption<T>& Max(const SharedOption<T> &lhs, const SharedOption<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}
