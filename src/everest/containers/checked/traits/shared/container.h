#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Container<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedChecked<E, T>& checked) noexcept {
    return Container<Checked<E, T>>::Length(*checked);
  }

  static constexpr bool IsEmpty(const SharedChecked<E, T>& checked) noexcept {
    return Container<Checked<E, T>>::IsEmpty(*checked);
  }

};

}