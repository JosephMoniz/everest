#ifndef TRAITOROUS_CONTAINERS_OPTION_MONAD_PLUS_H
#define TRAITOROUS_CONTAINERS_OPTION_MONAD_PLUS_H

#include "containers/option.h"
#include "traits/lawful/monad_plus.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template <class T>
class MonadPlus<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> MPlus(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}

#endif
