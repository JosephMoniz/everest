#ifndef TRAITOROUS_CONTAINERS_OPTION_EQ_H
#define TRAITOROUS_CONTAINERS_OPTION_EQ_H

#include "containers/option.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template <class T>
class Eq<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return Eq<LocalOption<T>>::Equals(*lhs.pointer(), *rhs.pointer());
  }

};

}

#endif
