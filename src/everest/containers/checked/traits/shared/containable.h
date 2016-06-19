#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Containable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const SharedChecked<E, T>& checked) noexcept {
    return Containable<Checked<E, T>>::Contains(item, *checked);
  }

};

}