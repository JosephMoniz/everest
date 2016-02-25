#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FILTERABLE
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FILTERABLE

#include "containers/option.h"
#include "traits/unlawful/filterable.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Filterable<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  template <class P>
  static constexpr LocalOption<T> Filter(P p, const LocalOption<T>& n) noexcept {
    return Match(n,
      []()            { return LocalNone<T>(); },
      [&](const T& m) { return p(m) ? n : LocalNone<T>(); }
    );
  }

};

}

#endif
