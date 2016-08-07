#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class E, class T>
class Checked;

template<class E, class T>
class Ord<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const Checked<E, T>& Min(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const Checked<E, T>& Max(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}