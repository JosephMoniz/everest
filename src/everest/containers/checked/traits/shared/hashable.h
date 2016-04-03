#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Hashable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const SharedChecked<E, T>& checked) noexcept {
    return Hashable<Checked<E, T>>::Hash(*checked);
  }

};

}