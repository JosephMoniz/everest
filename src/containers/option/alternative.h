#ifndef TRAITOROUS_CONTAINERS_OPTION_ALTERNATIVE_H
#define TRAITOROUS_CONTAINERS_OPTION_ALTERNATIVE_H

#include "containers/option.h"
#include "traits/lawful/alternative.h"

namespace traitorous {

template <class T>
class Alternative<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> Alt(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}

#endif
