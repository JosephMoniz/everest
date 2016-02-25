#ifndef TRAITOROUS_CONTAINERS_OPTION_ZERO_H
#define TRAITOROUS_CONTAINERS_OPTION_ZERO_H

#include "containers/option.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template<class T>
class ZeroVal<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> Zero() {
    return None<T>();
  }

};

}

#endif
