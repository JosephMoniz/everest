#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ZERO_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ZERO_H

#include "containers/local_option.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class ZeroVal<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalOption <T> Zero() {
    return LocalNone<T>();
  }

};

}

#endif
