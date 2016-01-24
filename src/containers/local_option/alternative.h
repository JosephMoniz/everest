#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ALTERNATIVE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ALTERNATIVE_H

#include "containers/local_option.h"
#include "traits/lawful/alternative.h"

namespace traitorous {

template <class T>
class alternative<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr local_option<T> alt(const local_option<T>& lhs,
                                       const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}

#endif
