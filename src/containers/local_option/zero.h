#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ZERO_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ZERO_H

#include "containers/local_option.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class zero_val<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr local_option<T> zero() {
    return local_none<T>();
  }

};

}

#endif
