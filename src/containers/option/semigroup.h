#ifndef TRAITOROUS_CONTAINERS_OPTION_SEMIGROUP_H
#define TRAITOROUS_CONTAINERS_OPTION_SEMIGROUP_H

#include "containers/option.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T>
class Semigroup<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option <T> Add(const Option <T>& lhs, const Option <T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return Match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return Some<T>(x + y); }
        );
      }
    );
  }

};

}

#endif

