#ifndef TRAITOROUS_CONTAINERS_OPTION_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_CONTAINABLE_H

#include "containers/option.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template <class T>
class Containable<Option<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const Option<T>& option) noexcept {
    return Containable<LocalOption<T>, T>::Contains(n, *option.Pointer());
  }

};

}

#endif
