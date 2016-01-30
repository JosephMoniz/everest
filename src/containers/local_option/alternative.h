#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ALTERNATIVE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ALTERNATIVE_H

#include "containers/local_option.h"
#include "traits/lawful/alternative.h"

namespace traitorous {

template <class T>
class Alternative<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalOption<T> Alt(const LocalOption<T>& lhs,
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
