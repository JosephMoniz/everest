#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_PLUS_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_PLUS_H

#include "containers/local_option.h"
#include "traits/lawful/monad_plus.h"

namespace traitorous {

template <class T>
class MonadPlus<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalOption<T> MPlus(const LocalOption<T>& lhs,
                                        const LocalOption<T>& rhs) noexcept
  {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}

#endif
