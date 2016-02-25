#ifndef TRAITOROUS_CONTAINERS_OPTION_UNWRAPPABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_UNWRAPPABLE_H

#include "containers/option.h"
#include "traits/unlawful/unwrappable.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template <class T>
class Unwrappable<Option<T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Option<T>& f) noexcept {
    return Unwrappable<LocalOption<T>>::GetOrElse(d, *f.Pointer());
  }

  static constexpr T GetOrDefault(const T& d, const Option<T>& n) noexcept {
    return Unwrappable<LocalOption<T>>::GetOrDefault(d, *n.Pointer());
  }

};

}

#endif
