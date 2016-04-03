#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/containers/option/traits/unwrappable.h>

namespace everest {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Unwrappable<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const SharedOption<T>& f) noexcept {
    return Unwrappable<Option<T>>::GetOrElse(d, *f);
  }

  static constexpr T GetOrDefault(const T& d, const SharedOption<T>& n) noexcept {
    return Unwrappable<Option<T>>::GetOrDefault(d, *n);
  }

};

}
