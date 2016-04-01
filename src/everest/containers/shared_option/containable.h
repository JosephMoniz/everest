#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Containable<SharedOption<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const SharedOption<T>& option) noexcept {
    return Containable<Option<T>, T>::Contains(n, *option.Pointer());
  }

};

}