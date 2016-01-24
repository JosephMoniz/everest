#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FILTERABLE
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FILTERABLE

#include "containers/local_option.h"
#include "traits/unlawful/filterable.h"

namespace traitorous {

template <class T>
class filterable<local_option<T>> {
public:

  static constexpr bool exists = true;

  template <class P>
  static constexpr local_option<T> filter(P p, const local_option<T>& n) noexcept {
    return match(n,
      []()            { return local_none<T>(); },
      [&](const T& m) { return p(m) ? n : local_none<T>(); }
    );
  }

};

}

#endif
