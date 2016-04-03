#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/unwrappable.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Unwrappable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const SharedChecked<E, T>& checked) noexcept {
    return Unwrappable<Checked<E, T>>::GetOrElse(d, *checked);
  }

  static constexpr T GetOrDefault(const T& d, const SharedChecked<E, T>& checked) noexcept {
    return Unwrappable<Checked<E, T>>::GetOrDefault(d, *checked);
  }

};

}