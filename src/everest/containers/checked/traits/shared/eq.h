#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Eq<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Eq<Checked<E, T>>::Equals(*lhs, *rhs);
  }

};

}