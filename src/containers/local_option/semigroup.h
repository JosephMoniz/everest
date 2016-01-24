#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_SEMIGROUP_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_SEMIGROUP_H

#include "containers/local_option.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T>
class semigroup<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr local_option<T> add(const local_option<T>& lhs, const local_option<T>& rhs) noexcept {
    return match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return local_some<T>(x + y); }
        );
      }
    );
  }

};

}

#endif
