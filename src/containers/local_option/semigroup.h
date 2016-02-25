#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_SEMIGROUP_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_SEMIGROUP_H

#include "containers/option.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Semigroup<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalOption<T> Add(const LocalOption<T>& lhs, const LocalOption<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return Match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return LocalSome<T>(x + y); }
        );
      }
    );
  }

};

}

#endif
